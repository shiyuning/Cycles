#include "Cycles.h"

void FieldOperation (int rotationYear, int y, int doy, CropManagementStruct *CropManagement, CommunityStruct *Community, SoilStruct *Soil, ResidueStruct *Residue, SimControlStruct *SimControl, SoilCarbonStruct *SoilCarbon, WeatherStruct *Weather, const char *project)
{
    FieldOperationStruct *plantingOrder;
    FieldOperationStruct *FixedFertilization;
    FieldOperationStruct *Tillage;
    FieldOperationStruct *FixedIrrigation;
    int             i;
    int             operation_index;
    int             kill_all = 0;

    /*
     * Perform planting if necessary
     */
    while (IsOperationToday (CropManagement->rotationYear, doy, CropManagement->plantingOrder, CropManagement->totalCropsPerRotation, &operation_index))
    {
        plantingOrder = &CropManagement->plantingOrder[operation_index];
        PlantingCrop (Community, CropManagement, operation_index);
        if (verbose_mode)
            printf ("DOY %3.3d %-20s %s\n", doy, "Planting", plantingOrder->cropName);
    }
    UpdateOperationStatus (CropManagement->plantingOrder, CropManagement->totalCropsPerRotation);

    /*
     * Perform fertilization if necessary
     */
    while (IsOperationToday (CropManagement->rotationYear, doy, CropManagement->FixedFertilization, CropManagement->numFertilization, &operation_index))
    {
        FixedFertilization = &CropManagement->FixedFertilization[operation_index];
        if (verbose_mode)
            printf ("DOY %3.3d %-20s %s\n", doy, "Fixed Fertilization", FixedFertilization->opSource);

        ApplyFertilizer (FixedFertilization, Soil, Residue);
    }
    UpdateOperationStatus (CropManagement->FixedFertilization, CropManagement->numFertilization);

    /*
     * Perform tillage/harvest if necessary
     */
    while (IsOperationToday (CropManagement->rotationYear, doy, CropManagement->Tillage, CropManagement->numTillage, &operation_index))
    {
        Tillage = &(CropManagement->Tillage[operation_index]);
        if (verbose_mode)
            printf ("DOY %3.3d %-20s %s\n", doy, "Tillage", Tillage->opToolName);

        if (strcasecmp (Tillage->opToolName, "Kill_Crop") != 0)
        {
            if (Tillage->grainHarvest || Tillage->forageHarvest)
            {
                if (Tillage->grainHarvest)
                {
                    if (strcasecmp (Tillage->cropNameT, "N/A") == 0 ||
                        strcasecmp (Tillage->cropNameT, "All") == 0)
                    {
                        kill_all = 1;
                    }

                    for (i = 0; i < Community->NumCrop; i++)
                    {
                        if (Community->Crop[i].stageGrowth > NO_CROP)
                        {
                            if (kill_all || strcasecmp (Tillage->cropNameT, Community->Crop[i].cropName) == 0)
                            {
                                GrainHarvest (y, doy, SimControl->simStartYear, &Community->Crop[i], Residue, Soil, SoilCarbon, Weather, project);
                            }
                        }
                    }
                }

                if (Tillage->forageHarvest)
                {
                    if (strcasecmp (Tillage->cropNameT, "N/A") == 0 ||
                        strcasecmp (Tillage->cropNameT, "All") == 0)
                    {
                        kill_all = 1;
                    }

                    for (i = 0; i < Community->NumCrop; i++)
                    {
                        if (Community->Crop[i].stageGrowth > NO_CROP)
                        {
                            if (kill_all || strcasecmp (Tillage->cropNameT, Community->Crop[i].cropName) == 0)
                            {
                                ForageHarvest (y, doy, SimControl->simStartYear, &Community->Crop[i], Residue, Soil, SoilCarbon, Weather, project);
                            }
                        }
                    }
                }

                UpdateCommunity (Community);
            }
            else
            {
                ExecuteTillage (SoilCarbon->abgdBiomassInput, Tillage, CropManagement->tillageFactor, Soil, Residue);
            }
        }
        else if (Community->NumActiveCrop > 0)
        {
            if (strcasecmp (Tillage->cropNameT, "N/A") == 0 ||
                strcasecmp (Tillage->cropNameT, "All") == 0)
            {
                kill_all = 1;
            }

            for (i = 0; i < Community->NumCrop; i++)
            {
                if (Community->Crop[i].stageGrowth > NO_CROP)
                {
                    if (kill_all || strcasecmp (Tillage->cropNameT, Community->Crop[i].cropName) == 0)
                    {
                        HarvestCrop (y, doy, SimControl->simStartYear, &Community->Crop[i], Residue, Soil, SoilCarbon, Weather, project);
                        Community->NumActiveCrop--;
                    }
                }
            }
        }
    }
    UpdateOperationStatus (CropManagement->Tillage, CropManagement->numTillage);

    UpdateCommunity (Community);

    /*
     * Perform irrigation if neccesary
     */
    Soil->irrigationVol = 0.0;
    while (IsOperationToday (CropManagement->rotationYear, doy, CropManagement->FixedIrrigation, CropManagement->numIrrigation, &operation_index))
    {
        FixedIrrigation = &(CropManagement->FixedIrrigation[operation_index]);
        if (verbose_mode)
            printf ("DOY %3.3d %-20s %lf\n", doy, "Irrigation", FixedIrrigation->opVolume);

        Soil->irrigationVol += FixedIrrigation->opVolume;
    }
    UpdateOperationStatus (CropManagement->FixedIrrigation, CropManagement->numIrrigation);
}
    
int IsOperationToday (int rotationYear, int doy, FieldOperationStruct *FieldOperation, int numOperation, int *operationIndex)
{
    /*
     * Returns a true or false indicating if an operation happens on that day
     * -----------------------------------------------------------------------
     * LOCAL VARIABLES
     *
     * Variable             Type        Description
     * ==========           ==========  ====================
     * operation_today	    int		[return value]
     */
    int             operation_today;
    int             i;

    operation_today = 0;
    *operationIndex = -1;

    if  (numOperation <= 0)
    {
        operation_today = 0;
        *operationIndex = -1;
    }
    else
    {
        for (i = 0; i < numOperation; i++)
        {
            if (FieldOperation[i].status == 1)
                continue;
            else
            {
                if (rotationYear == FieldOperation[i].opYear && doy == FieldOperation[i].opDay)
                {
                    operation_today = 1;
                    FieldOperation[i].status = 1;
                    *operationIndex = i;

                    break;
                }
                else
                    break;
            }
        }
    }

    return (operation_today);
}

void UpdateOperationStatus (FieldOperationStruct *FieldOperation, int numOperation)
{
    int             i;
    int             all_performed = 1;

    if (numOperation <= 0)
    {
        /* Do nothing */
    }
    else
    {
        for (i = 0; i < numOperation; i++)
        {
            if (FieldOperation[i].status == 0)
            {
                all_performed = 0;
                break;
            }
        }

        if (all_performed)
        {
            for (i = 0 ; i < numOperation; i++)
                FieldOperation[i].status = 0;
        }
    }
}
