#include "Cycles.h"

void ReadOperation (char *filename, cropmgmt_struct *CropManagement, const comm_struct *Community, int yearsInRotation)
{
    /*
     * Read field operation description file
     * -----------------------------------------------------------------------
     * LOCAL VARIABLES
     *
     * Variable             Type        Description
     * ==========           ==========  ====================
     * operation_file	    FILE*	File pointer of fiedl operation file
     * fullname		    char*	Full file name of the field operation
     *					  file
     * cmdstr		    char[MAXSTRING]
     *					Command string
     * optstr		    char[MAXSTRING]
     *					Option argument string
     * tillage_counter	    int		Tillage operation counter
     * planting_counter	    int		Planting operatin counter
     * irrigation_counter   int		Fixed irrigation operation counter
     * fertilization_counter
     *			    int		Fixed fertilization operation counter
     * auto_irrigation_counter
     *			    int		Automatic irrigation operation counter
     * harvest_counter	    int		Forced harvest operation counter
     * tempyear		    int
     * i		    int		Loop counter
     * j		    int		Loop counter
     * q		    op_struct*
     */
    FILE           *operation_file;
    char           *fullname;
    char            cmdstr[MAXSTRING];
    int             tillage_counter = 0;
    int             planting_counter = 0;
    int             irrigation_counter = 0;
    int             fertilization_counter = 0;
    int             auto_irrigation_counter = 0;
    int             i, j;
    op_struct *q;

    /* Open field operation file */
    fullname = (char *)malloc ((strlen (filename) + 7) * sizeof (char));
    sprintf (fullname, "input/%s", filename);
    operation_file = fopen (fullname, "r");

    if (operation_file == NULL)
    {
        printf ("ERROR: Cannot find the field operation file %s!\n", filename);
        exit (1);
    }
    else
        printf ("%-30s input/%s.\n", "Read field operation file:", filename);

    free (fullname);

    /* Read field operation file and count numbers of operations */
    FindLine (operation_file, "BOF");
    planting_counter = CountOccurance (operation_file, "PLANTING");

    FindLine (operation_file, "BOF");
    tillage_counter = CountOccurance (operation_file, "TILLAGE");
    
    FindLine (operation_file, "BOF");
    irrigation_counter = CountOccurance (operation_file, "FIXED_IRRIGATION");

    FindLine (operation_file, "BOF");
    fertilization_counter = CountOccurance (operation_file, "FIXED_FERTILIZATION");

    FindLine (operation_file, "BOF");
    auto_irrigation_counter = CountOccurance (operation_file, "AUTO_IRRIGATION");

    /* Allocate memories for field operation classes */
    CropManagement->totalCropsPerRotation = planting_counter;
    CropManagement->plantingOrder = (op_struct *)malloc (planting_counter * sizeof (op_struct));

    CropManagement->numFertilization = fertilization_counter;
    CropManagement->FixedFertilization = (op_struct *)malloc (fertilization_counter * sizeof (op_struct));

    CropManagement->numIrrigation = irrigation_counter;
    CropManagement->FixedIrrigation = (op_struct *)malloc (irrigation_counter * sizeof (op_struct));

    CropManagement->numTillage = tillage_counter;
    CropManagement->Tillage = (op_struct *)malloc (tillage_counter * sizeof (op_struct));

    CropManagement->numAutoIrrigation = auto_irrigation_counter;
    CropManagement->autoIrrigation = (autoirr_struct *)malloc (auto_irrigation_counter * sizeof (autoirr_struct));
    CropManagement->usingAutoIrr = 0;

    if (planting_counter)
    {
        /* Rewind to the beginning of file and read all planting operations */
        FindLine (operation_file, "BOF");

        for (i = 0; i < planting_counter; i++)
        {
            q = &(CropManagement->plantingOrder[i]);

            FindLine (operation_file, "PLANTING");

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "YEAR", &q->opYear);
            if (q->opYear > yearsInRotation)
            {
                printf ("ERROR: Operation year is larger than years in rotation!\n");
                printf ("Please remove this operation and retry.\n");
            }

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "DOY", &q->opDay);
            
            NextLine (operation_file, cmdstr);
            ReadKeywordStr (cmdstr, "CROP", q->cropName);

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "AUTO_IRRIGATION", &q->usesAutoIrrigation);
            if (CropManagement->plantingOrder[i].usesAutoIrrigation == 0)
                CropManagement->plantingOrder[i].usesAutoIrrigation = -1;
            else
                CropManagement->usingAutoIrr = 1;

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "AUTO_FERTILIZATION", &q->usesAutoFertilization);
            if (CropManagement->plantingOrder[i].usesAutoFertilization == 0)
                CropManagement->plantingOrder[i].usesAutoFertilization = -1;

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "FRACTION", &q->plantingDensity);

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "CLIPPING_START", &q->clippingStart);
            if (q->clippingStart > 366 || q->clippingStart < 1)
            {
                printf ("ERROR: Please specify valid DOY for clipping start date!\n");
                exit (1);
            }
            
            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "CLIPPING_END", &q->clippingEnd);
            if (q->clippingEnd > 366 || q->clippingEnd < 1)
            {
                printf ("ERROR: Please specify valid DOY for clipping end date!\n");
                exit (1);
            }

            q->status = 0;

            /* Link planting order and crop description */
            for (j = 0; j < Community->NumCrop; j++)
            {
                if (strcmp (CropManagement->plantingOrder[i].cropName, Community->Crop[j].cropName) == 0)
                {
                    CropManagement->plantingOrder[i].plantID = j;
                    break;
                }
            }
            if (j >= Community->NumCrop)
            {
                printf ("ERROR: Cannot find the plant description of %s, please check your input file\n", CropManagement->plantingOrder[i].cropName);
                exit (1);
            }
        }
    }

    if (tillage_counter)
    {
        /* Rewind to the beginning of file and read all tillage operations */
        FindLine (operation_file, "BOF");

        for (i = 0; i < tillage_counter; i++)
        {
            q = &(CropManagement->Tillage[i]);

            FindLine (operation_file, "TILLAGE");

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "YEAR", &q->opYear);
            if (q->opYear > yearsInRotation)
            {
                printf ("ERROR: Operation year is larger than years in rotation!\n");
                printf ("Please remove this operation and retry.\n");
            }

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "DOY", &q->opDay);

            NextLine (operation_file, cmdstr);
            ReadKeywordStr (cmdstr, "TOOL", q->opToolName);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "DEPTH", &q->opDepth);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "SOIL_DISTURB_RATIO", &q->opSDR);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "MIXING_EFFICIENCY", &q->opMixingEfficiency);

            NextLine (operation_file, cmdstr);
            ReadKeywordStr (cmdstr, "CROP_NAME", q->cropNameT);

            /* Check if the specified crop exists */
            if (strcasecmp (q->cropNameT, "N/A") != 0 &&
                strcasecmp (q->cropNameT, "All") != 0 &&
                !CropExist (q->cropNameT, Community))
            {
                printf ("ERROR: Crop name %s not recognized!\n", q->cropNameT);
                exit (1);
            }

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "FRAC_THERMAL_TIME", &q->fractionThermalTime);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "KILL_EFFICIENCY", &q->killEfficiency);

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "GRAIN_HARVEST", &q->grainHarvest);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "FORAGE_HARVEST", &q->forageHarvest);

            q->status = 0;
        }
    }

    if (irrigation_counter)
    {
        /* Rewind to the beginning of file and read all irrigation
         * operations */
        FindLine (operation_file, "BOF");

        for (i = 0; i < irrigation_counter; i++)
        {
            q = &(CropManagement->FixedIrrigation[i]);

            FindLine (operation_file, "FIXED_IRRIGATION");

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "YEAR", &q->opYear);
            if (q->opYear > yearsInRotation)
            {
                printf ("ERROR: Operation year is larger than years in rotation!\n");
                printf ("Please remove this operation and retry.\n");
            }
            
            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "DOY", &q->opDay);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "VOLUME", &q->opVolume);

            q->status = 0;
        }
    }

    if (fertilization_counter)
    {
        /* Rewind to the beginning of file and read all fertilization
         * operations */
        FindLine (operation_file, "BOF");

        for (i = 0; i < fertilization_counter; i++)
        {
            q = &(CropManagement->FixedFertilization[i]);

            FindLine (operation_file, "FIXED_FERTILIZATION");

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "YEAR", &q->opYear);
            if (q->opYear > yearsInRotation)
            {
                printf ("ERROR: Operation year is larger than years in rotation!\n");
                printf ("Please remove this operation and retry.\n");
            }

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "DOY", &q->opDay);

            NextLine (operation_file, cmdstr);
            ReadKeywordStr (cmdstr, "SOURCE", q->opSource);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "MASS", &q->opMass);

            NextLine (operation_file, cmdstr);
            ReadKeywordStr (cmdstr, "FORM", q->opForm);

            NextLine (operation_file, cmdstr);
            ReadKeywordStr (cmdstr, "METHOD", q->opMethod);

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "LAYER", &q->opLayer);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "C_ORGANIC", &q->opC_Organic);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "C_CHARCOAL", &q->opC_Charcoal);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "N_ORGANIC", &q->opN_Organic);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "N_CHARCOAL", &q->opN_Charcoal);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "N_NH4", &q->opN_NH4);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "N_NO3", &q->opN_NO3);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "P_ORGANIC", &q->opP_Organic);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "P_CHARCOAL", &q->opP_Charcoal);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "P_INORGANIC", &q->opP_Inorganic);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "K", &q->opK);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "S", &q->opS);

            q->status = 0;

            if (q->opC_Organic + q->opC_Charcoal + q->opN_Organic + q->opN_Charcoal + q->opN_NH4 + q->opN_NO3 + q->opP_Organic + q->opP_Charcoal + q->opP_Inorganic + q->opK + q->opS <= 1.0)
            {
                q->opMass /= 1000.0;
            }
            else
            {
                printf ("ERROR: Added fertilization fractions must be <= 1\n");
                exit (1);
            }
        }
    }

    if (CropManagement->usingAutoIrr)
    {
        /* Rewind to the beginning of file and read all planting operations */
        FindLine (operation_file, "BOF");

        for (i = 0; i < auto_irrigation_counter; i++)
        {
            FindLine (operation_file, "AUTO_IRRIGATION");

            NextLine (operation_file, cmdstr);
            ReadKeywordStr (cmdstr, "CROP", CropManagement->autoIrrigation[i].cropName);

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "START_DAY", &CropManagement->autoIrrigation[i].startDay);

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "STOP_DAY", &CropManagement->autoIrrigation[i].stopDay);

            NextLine (operation_file, cmdstr);
            ReadKeywordDouble (cmdstr, "WATER_DEPLETION", &CropManagement->autoIrrigation[i].waterDepletion);

            NextLine (operation_file, cmdstr);
            ReadKeywordInt (cmdstr, "LAST_SOIL_LAYER", &CropManagement->autoIrrigation[i].lastSoilLayer);
        }
    }

    /* Link plating order and auto irrigation */
    for (i = 0; i < CropManagement->totalCropsPerRotation; i++)
    {
        if (CropManagement->usingAutoIrr && CropManagement->plantingOrder[i].usesAutoIrrigation == 1)
        {
            for (j = 0; j < auto_irrigation_counter; j++)
            {
                if (strcmp (CropManagement->plantingOrder[i].cropName, CropManagement->autoIrrigation[j].cropName) == 0)
                {
                    CropManagement->plantingOrder[i].usesAutoIrrigation = j;
                    break;
                }
            }
            if (j >= auto_irrigation_counter)
            {
                printf ("ERROR: Cannot find the description of auto irrigation for %s!\n", CropManagement->plantingOrder[i].cropName);
                exit (1);
            }
        }
        else
            CropManagement->plantingOrder[i].usesAutoIrrigation = -1;
    }

    fclose (operation_file);

    if (debug_mode)
    {
        PrintOperation (CropManagement->plantingOrder,
            CropManagement->totalCropsPerRotation,
            CropManagement->Tillage, CropManagement->numTillage,
            CropManagement->FixedIrrigation, CropManagement->numIrrigation,
            CropManagement->FixedFertilization, CropManagement->numFertilization);
    }
}

int CropExist (char *cropName, const comm_struct *Community)
{
    int             i;
    int             exist = 0;


    for (i = 0; i < Community->NumCrop; i++)
    {
        if (strcmp (cropName, Community->Crop[i].cropName) == 0)
        {
            exist = 1;
            break;
        }
    }

    return (exist);
}
