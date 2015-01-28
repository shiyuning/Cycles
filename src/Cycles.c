#include "include/Cycles.h"

int verbose_mode;

int main (int argc, char *argv[])
{
    int rotationYear;
    int nextSeedingDate;
    int nextSeedingYear;
    int y;
    int doy;
    int i;
    int c;
    clock_t begin, end;

    CyclesStruct    Cycles;     /* Model structure */
    char           *project;    /* Name of simulation */

    begin = clock();

    Cycles = (CyclesStruct) malloc (sizeof (*Cycles));


    system ("clear");
    printf ("\n\n");
    printf ("\t\t ######  ##    ##  ######  ##       ########  ######\n");
    printf ("\t\t##    ##  ##  ##  ##    ## ##       ##       ##    ##\n");
    printf ("\t\t##         ####   ##       ##       ##       ##\n");
    printf ("\t\t##          ##    ##       ##       ######    ######\n");
    printf ("\t\t##          ##    ##       ##       ##             ##\n");
    printf ("\t\t##    ##    ##    ##    ## ##       ##       ##    ##\n");
    printf ("\t\t ######     ##     ######  ######## ########  ######\n\n\n");

    verbose_mode = 0;

    while((c = getopt(argc, argv, "v")) != -1)
    {
        if (optind >= argc)
        {
            printf ("\nUsage: ./Cycles [-v] <project name>\n");
            printf ("\t-v Verbose mode\n");
            exit (1);
        }
        switch(c)
        {
            case 'v':
                verbose_mode = 1;
                printf ("Verbose mode turned on.\n");
                break;
            case '?':
                printf ("Option not recognisable %s\n", argv[optind]);
                break;
            default:
                break;
        }
    }

    if (optind >= argc)
    {
        printf ("ERROR: Please specify the name of project!\n");
        printf ("\nUsage: ./Cycles [-v] <project name>\n");
        printf ("\t-v Verbose mode\n");
        exit (1);
    }
    else
    {
        project = (char *)malloc ((strlen (argv[optind]) + 1) * sizeof (char));
        strcpy (project, argv[optind]);
    }

    printf ("Now running the %s simulation.\n\n", project);

    InitializeOutput (project);

    /* Read simulation control input file */
    ReadSimControl (project, &Cycles->SimControl);
#ifdef _DEBUG_
    PrintSimContrl (Cycles->SimControl);
#endif

    /* Read soil description file */
    ReadSoil (project, &Cycles->Soil);
#ifdef _DEBUG_
    PrintSoil (Cycles->Soil);
#endif

    /* Read crop description file */
    ReadCrop (project, &Cycles->CropManagement);
#ifdef _DEBUG_
    PrintCrop (Cycles->CropManagement.describedCrop, Cycles->CropManagement.NumDescribedCrop);
#endif

    /* Read field operation file */
    ReadOperation (project, &Cycles->CropManagement, Cycles->SimControl.yearsInRotation);
#ifdef _DEBUG_
    PrintOperation (Cycles->CropManagement.plantingOrder, Cycles->CropManagement.totalCropsPerRotation, Cycles->CropManagement.Tillage, Cycles->CropManagement.numTillage, Cycles->CropManagement.FixedIrrigation, Cycles->CropManagement.numIrrigation, Cycles->CropManagement.FixedFertilization, Cycles->CropManagement.numFertilization);
#endif

    /* Read meteorological driver */
    ReadWeather (project, &Cycles->Weather, Cycles->SimControl.simStartYear, Cycles->SimControl.totalYears);
#ifdef _DEBUG_
    PrintWeather (Cycles->Weather);
#endif

    /* Initialize model variables and parameters */
    Initialize (&Cycles->SimControl, &Cycles->Weather, &Cycles->Soil, &Cycles->Residue, &Cycles->SoilCarbon, &Cycles->Crop, &Cycles->CropManagement, &Cycles->Snow);

    /* Compute crop thermal time */
    printf ("Compute crop thermal time.\n");
    ComputeThermalTime (Cycles->SimControl.totalYears, &Cycles->CropManagement, &Cycles->Weather);

    SelectCropInitialPosition (&Cycles->CropManagement);

    if (Cycles->CropManagement.totalCropsPerRotation > 0)
    {
        nextSeedingYear = Cycles->CropManagement.nextCropSeedingYear;
        nextSeedingDate = Cycles->CropManagement.nextCropSeedingDate;
    }
    else
    {
        nextSeedingYear = 0;
        nextSeedingDate = 0;
    }
#ifdef _DEBUG_
    printf ("*Next seeding year is %-4d, next seeding date is %3d\n", nextSeedingYear, nextSeedingDate);
#endif

    rotationYear = 0;

    printf ("\nSimulation running ...\n");

    for (y = 0; y < Cycles->SimControl.totalYears; y++)
    {
        printf ("Year %4d\n", y + 1);
        if (rotationYear < Cycles->SimControl.yearsInRotation)
            rotationYear++;
        else
            rotationYear = 1;
#ifdef _DEBUG_
        printf ("*%-15s = %-d\n", "Rotation year", rotationYear);
#endif

        SelectOperationYear (rotationYear, Cycles->CropManagement.Tillage, Cycles->CropManagement.numTillage, &Cycles->CropManagement.tillageIndex);
        SelectOperationYear (rotationYear, Cycles->CropManagement.FixedIrrigation, Cycles->CropManagement.numIrrigation, &Cycles->CropManagement.irrigationIndex);
        SelectOperationYear (rotationYear, Cycles->CropManagement.FixedFertilization, Cycles->CropManagement.numFertilization, &Cycles->CropManagement.fertilizationIndex);

        for (i = 0; i < Cycles->Soil.totalLayers; i++)
        {
            Cycles->SoilCarbon.carbonMassInitial[i] = Cycles->Soil.SOC_Mass[i];
            Cycles->SoilCarbon.carbonMassFinal[i] = 0.;
            Cycles->SoilCarbon.annualHumifiedCarbonMass[i] = 0.;
            Cycles->SoilCarbon.annualRespiredCarbonMass[i] = 0.;
        } 

        /* Daily operations */
        for (doy = 1; doy < 366; doy++)
        {
#ifdef _DEBUG_
            printf ("DOY %3.3d\n", doy);
#endif
            DailyOperations (rotationYear, y, doy, &nextSeedingYear, &nextSeedingDate, &Cycles->CropManagement, &Cycles->Crop, &Cycles->Residue, &Cycles->SimControl, &Cycles->Snow, &Cycles->Soil, &Cycles->SoilCarbon, &Cycles->Weather, project);
            PrintDailyOutput (y, doy, Cycles->SimControl.simStartYear, &Cycles->Weather, &Cycles->Crop, &Cycles->Soil, &Cycles->Snow, project);
        }
    }
    
    end = clock();

    printf ("\nSimulation time: %-lf seconds.\n", (double)(end - begin) / CLOCKS_PER_SEC);

    return 0;
}
