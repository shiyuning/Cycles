#include "Cycles.h"

void InitializeOutput (char *project)
{
    char            filename[50];
    char           *output_dir;
    FILE           *output_file;

    output_dir = (char *)malloc ((strlen (project) + 8) * sizeof (char));

    mkdir ("output", 0755);
    sprintf (output_dir, "output/%s", project);
    mkdir (output_dir, 0755);

    sprintf (filename, "output/%s/weather.dat", project);
    output_file = fopen (filename, "w");
    fprintf (output_file, "%-10s\t%-7s\t%-7s\t%-7s\n", "DATE", "T_MEAN", "ET_REF", "PRECIP");
    fprintf (output_file, "%-10s\t%-7s\t%-7s\t%-7s\n", "YYYY-MM-DD", "C", "MM/DAY", "MM");
    fclose (output_file);

    sprintf (filename, "output/%s/crop.dat", project);
    output_file = fopen (filename, "w");
    fprintf (output_file, "%-10s\t%-15s\t%-23s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", " DATE", " CROP", " STAGE", "THERMAL", "CUMULAT", "  ABG", " ROOT", " FRACT", " TOTAL", "  ABG", " ROOT", " ABG N", "   N", "N ADDED", "   N", " WATER", "POTENT");
    fprintf (output_file, "%-10s\t%-15s\t%-23s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", "", "", "", " TIME", "BIOMASS", "BIOMASS", "BIOMASS", "INTERCP", "   N", "   N", "   N", "CONCENT", "  FIX", "", "STRESS", "STRESS", "TRANSP");
    fprintf (output_file, "%-10s\t%-15s\t%-23s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", "YYYY-MM-DD", "-", "-", "C-DAY", "Mg/ha", "Mg/ha", "Mg/ha", "-", "kg/ha", "kg/ha", "kg/ha", "g/kg", "kg/ha", "kg/ha", "%", "%", "mm/day");
    fclose (output_file);

    sprintf (filename, "output/%s/season.dat", project);
    output_file = fopen (filename, "w");
    fprintf (output_file, "%-10s\t%-15s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", "DATE", "CROP", "TOTAL", "ROOT", "GRAIN", "FORAGE", "AVG", "HARVEST", "POTENT", "ACTUAL", "SOIL", "TOTAL N", "ROOT N", "GRAIN N", "FORAGE", "CUMUL N");
    fprintf (output_file, "%-10s\t%-15s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", "", "", "BIOMASS", "BIOMASS", "YIELD", "YIELD", "RESIDUE", "INDEX", "TRANSP", "TRANSP", "EVAP", "", "", "", "   N", "STRESS");
    fprintf (output_file, "%-10s\t%-15s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", "YYYY-MM-DD", "N/A", "Mg/ha", "Mg/ha", "Mg/ha", "Mg/ha", "Mg/ha", "Mg/Mg", "mm", "mm", "mm", "Mg/ha", "Mg/ha", "Mg/ha", "Mg/ha", "");
    fclose (output_file);

    sprintf (filename, "output/%s/water.dat", project);
    output_file = fopen (filename, "w");
    fprintf (output_file, "%-10s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", "DATE", "IRRIG", "RUNOFF", "INFILT", "DRAIN", "SOIL E", "RES E", "SNOW S", "TRANSP");
    fprintf (output_file, "%-10s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", "YYYY-MM-DD", "mm/day", "mm/day", "mm/day", "mm/day", "mm/day", "mm/day", "mm/day", "mm/day");
    fclose (output_file);

    sprintf (filename, "output/%s/N.dat", project);
    output_file = fopen (filename, "w");
    fprintf (output_file, "%-10s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", "DATE", "SON", "NO3", "NH4", "MINERAL", "IMMOBIL", "NET", "NH4", "N2O", "NH4", "NO3", "N2O", "NO3", "NO4");
    fprintf (output_file, "%-10s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", "", "PROFILE", "PROFILE", "PROFILE", "", "", "MINERAL", "NITRIF", "NITRIF", "VOLATIL", "DENITRI", "DENITRI", "LEACH", "LEACH");
    fprintf (output_file, "%-10s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\t%-7s\n", "YYYY-MM-DD", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha");
    fclose (output_file);

    sprintf (filename, "output/%s/residue.dat", project);
    output_file = fopen (filename, "w");
    fclose (output_file);

    sprintf (filename, "output/%s/C.dat", project);
    output_file = fopen (filename, "w");
    fprintf (output_file, "%-10s\t%-7s\t%-7s\t%-7s\t%-7s\n", "DATE", "SOC", "HUMIF", "RES R", "SOM R");
    fprintf (output_file, "%-10s\t%-7s\t%-7s\t%-7s\t%-7s\n", "YYYY-MM-DD", "Mg/ha", "Mg/ha", "Mg/ha", "Mg/ha");
    fclose (output_file);

    free (output_dir);
}

void PrintDailyOutput (int y, int doy, int start_year, const WeatherStruct *Weather, const CropStruct *Crop, const SoilStruct *Soil, const SnowStruct *Snow, const ResidueStruct *Residue, const char *project)
{
    char            filename[50];
    FILE           *output_file;
    int             month, mday;
    int             i;
    double          sum;

    doy2date (y + start_year, doy, &month, &mday, 0);

    /*
     * Print weather output
     */
    sprintf (filename, "output/%s/weather.dat", project);
    output_file = fopen (filename, "a");

    fprintf (output_file, "%4.4d-%2.2d-%2.2d\t", y + start_year, month, mday);
    fprintf (output_file, "%-7.2lf\t", 0.5 * Weather->tMin[y][doy - 1] + 0.5 * Weather->tMax[y][doy - 1]);
    fprintf (output_file, "%-7.3lf\t", Weather->ETref[y][doy - 1]);
    fprintf (output_file, "%-7.2lf\n", Weather->precipitation[y][doy - 1]);

    fflush (output_file);
    fclose (output_file);

    /*
     * Print crop output
     */
    sprintf (filename, "output/%s/crop.dat", project);
    output_file = fopen (filename, "a");

    fprintf (output_file, "%4.4d-%2.2d-%2.2d\t", y + start_year, month, mday);
    if (Crop->cropUniqueIdentifier < 0)
    {
        fprintf (output_file, "%-15s\t", "Fallow");
        fprintf (output_file, "%-23s\t", "N/A");
    }
    else
    {
        fprintf (output_file, "%-15s\t", Crop->cropName);
        switch (Crop->stageGrowth)
        {
            case PRE_EMERGENCE:
                fprintf (output_file, "%-23s\t", "PRE_EMERGENCE");
                break;
            case VEGETATIVE_GROWTH:
                fprintf (output_file, "%-23s\t", "VEGETATIVE_GROWTH");
                break;
            case PERENNIAL:
                fprintf (output_file, "%-23s\t", "PERENNIAL");
                break;
            case REPRODUCTIVE_GROWTH:
                fprintf (output_file, "%-23s\t", "REPRODUCTIVE_GROWTH");
                break;
            case MATURITY:
                fprintf (output_file, "%-23s\t", "MATURITY");
                break;
            case CLIPPING:
                fprintf (output_file, "%-23s\t", "CLIPPING");
                break;
            case PLANTING:
                fprintf (output_file, "%-23s\t", "PLANTING");
                break;
        }
    }

    fprintf (output_file, "%-7.2lf\t", Crop->svTT_Cumulative);
    fprintf (output_file, "%-7.3lf\t", Crop->svBiomass);
    fprintf (output_file, "%-7.3lf\t", Crop->svShoot);
    fprintf (output_file, "%-7.3lf\t", Crop->svRoot);
    fprintf (output_file, "%-7.4lf\t", Crop->svRadiationInterception);
    fprintf (output_file, "%-7.2lf\t", (Crop->svN_Shoot + Crop->svN_Root) * 1000.);
    fprintf (output_file, "%-7.2lf\t", Crop->svN_Shoot * 1000.);
    fprintf (output_file, "%-7.2lf\t", Crop->svN_Root * 1000.);
    if (Crop->svShoot > 0.)
        fprintf (output_file, "%-7.2lf\t", (Crop->svN_Shoot / Crop->svShoot) * 1000.);
    else
        fprintf (output_file, "%-7.2lf\t", 0.);
    fprintf (output_file, "%-7.2lf\t", Crop->svN_Fixation * 1000.);
    fprintf (output_file, "%-7.2lf\t", Crop->svN_AutoAdded * 1000.);
    fprintf (output_file, "%-7.2lf\t", Crop->svN_StressFactor);
    fprintf (output_file, "%-7.2lf\t", Crop->svWaterStressFactor);
    fprintf (output_file, "%-7.2lf\n", Crop->svTranspirationPotential);

    fflush (output_file);
    fclose (output_file);

    /*
     * Print Water output
     */
    sprintf (filename, "output/%s/water.dat", project);
    output_file = fopen (filename, "a");

    fprintf (output_file, "%4.4d-%2.2d-%2.2d\t", y + start_year, month, mday);
    fprintf (output_file, "%-7.3lf\t", Soil->irrigationVol);
    fprintf (output_file, "%-7.3lf\t", Soil->runoffVol);
    fprintf (output_file, "%-7.3lf\t", Soil->infiltrationVol);
    fprintf (output_file, "%-7.3lf\t", Soil->drainageVol);
    fprintf (output_file, "%-7.3lf\t", Soil->evaporationVol);
    fprintf (output_file, "%-7.3lf\t", Soil->residueEvaporationVol);
    fprintf (output_file, "%-7.3lf\t", Snow->snowEvaporationVol);
    fprintf (output_file, "%-7.3lf\n", Crop->svTranspiration);

    fflush (output_file);
    fclose (output_file);

    /*
     * Print Nitrogen Output
     */
    sprintf (filename, "output/%s/N.dat", project);
    output_file = fopen (filename, "a");

    fprintf (output_file, "%4.4d-%2.2d-%2.2d\t", y + start_year, month, mday);
    fprintf (output_file, "%-7.1lf\t", Soil->SONProfile * 1000.);
    fprintf (output_file, "%-7.2lf\t", Soil->NO3Profile * 1000.);
    fprintf (output_file, "%-7.3lf\t", Soil->NH4Profile * 1000.);
    fprintf (output_file, "%-7.4lf\t", Soil->N_Mineralization * 1000.);
    fprintf (output_file, "%-7.3lf\t", Soil->N_Immobilization * 1000.);
    fprintf (output_file, "%-7.3lf\t", Soil->N_NetMineralization * 1000.);
    fprintf (output_file, "%-7.4lf\t", Soil->NH4_Nitrification * 1000.);
    fprintf (output_file, "%-7.5lf\t", Soil->N2O_Nitrification * 1000.);
    fprintf (output_file, "%-7.5lf\t", Soil->NH4_Volatilization * 1000.);
    fprintf (output_file, "%-7.5lf\t", Soil->NO3_Denitrification * 1000.);
    fprintf (output_file, "%-7.5lf\t", Soil->N2O_Denitrification * 1000.);
    fprintf (output_file, "%-7.5lf\t", Soil->NO3Leaching * 1000.);
    fprintf (output_file, "%-7.5lf\n", Soil->NH4Leaching * 1000.);

    fflush (output_file);
    fclose (output_file);

    /*
     * Print Carbon Output
     */
    sprintf (filename, "output/%s/C.dat", project);
    output_file = fopen (filename, "a");

    fprintf (output_file, "%4.4d-%2.2d-%2.2d\t", y + start_year, month, mday);
    fprintf (output_file, "%-7.2lf\t", Soil->SOCProfile);
    fprintf (output_file, "%-7.5lf\t", Soil->C_Humified);
    fprintf (output_file, "%-7.5lf\t", Soil->C_ResidueRespired);
    fprintf (output_file, "%-7.5lf\n", Soil->C_SoilRespired);

    fflush (output_file);
    fclose (output_file);

    /*
     * Print residue output
     */
    sprintf (filename, "output/%s/residue.dat", project);
    output_file = fopen (filename, "a");

    fprintf (output_file, "%4.4d-%2.2d-%2.2d\t", y + start_year, month, mday);
    fprintf (output_file, "%-7.4lf\t", Residue->residueInterception);
    fprintf (output_file, "%-7.4lf\t", Residue->stanResidueMass + Residue->flatResidueMass);
    sum = 0.0;
    for (i = 0; i < Soil->totalLayers; i++)
        sum = sum + Residue->residueAbgd[i];
    fprintf (output_file, "%-7.4lf\t", sum);
    sum = 0.0;
    for (i = 0; i < Soil->totalLayers; i++)
        sum = sum + Residue->residueRt[i] + Residue->residueRz[i];
    fprintf (output_file, "%-7.4lf\t", sum);
    fprintf (output_file, "%-7.5lf\t", Residue->manureSurfaceC);
    fprintf (output_file, "%-7.5lf\t", Residue->stanResidueN + Residue->flatResidueN);
    sum = 0.0;
    for (i = 0; i < Soil->totalLayers; i++)
        sum = sum + Residue->residueAbgdN[i];
    fprintf (output_file, "%-7.5lf\t", sum);
    sum = 0.0;
    for (i = 0; i < Soil->totalLayers; i++)
        sum = sum + Residue->residueRtN[i] + Residue->residueRzN[i];
    fprintf (output_file, "%-7.5lf\t", sum);
    fprintf (output_file, "%-7.5lf\t", Residue->manureSurfaceN);
    if (Residue->stanResidueMass > 0.0)
        fprintf (output_file, "%-7.5lf\t", Residue->stanResidueWater / (Residue->stanResidueWater + Residue->stanResidueMass / 10.0));
    else
        fprintf (output_file, "%-7.5lf\t", 0.0);
    if (Residue->flatResidueMass > 0.0)
        fprintf (output_file, "%-7.5lf\n", Residue->flatResidueWater / (Residue->flatResidueWater + Residue->flatResidueMass / 10.0));
    else
        fprintf (output_file, "%-7.5lf\n", 0.0);

    fflush (output_file);
    fclose (output_file);
}

void PrintSeasonOutput (int y, int doy, int start_year, const CropStruct *Crop, const char *project)
{
    char            filename[50];
    FILE           *output_file;
    int             month, mday;

    sprintf (filename, "output/%s/season.dat", project);
    output_file = fopen (filename, "a");

    doy2date (y + start_year, doy, &month, &mday, 0);
    fprintf (output_file, "%4.4d-%2.2d-%2.2d\t", y + start_year, month, mday);
    fprintf (output_file, "%-15s\t", Crop->cropName);

    fprintf (output_file, "%-7.3lf\t", Crop->rcBiomass);
    fprintf (output_file, "%-7.3lf\t", Crop->rcRoot);
    fprintf (output_file, "%-7.3lf\t", Crop->rcGrainYield);
    fprintf (output_file, "%-7.3lf\t", Crop->rcForageYield);
    fprintf (output_file, "%-7.3lf\t", Crop->rcResidueBiomass);
    fprintf (output_file, "%-7.4lf\t", Crop->rcHarvestIndex);
    fprintf (output_file, "%-7.2lf\t", Crop->rcCropTranspirationPotential);
    fprintf (output_file, "%-7.2lf\t", Crop->rcCropTranspiration);
    fprintf (output_file, "%-7.2lf\t", Crop->rcSoilWaterEvaporation);
    fprintf (output_file, "%-7.3lf\t", Crop->rcTotalNitrogen);
    fprintf (output_file, "%-7.4lf\t", Crop->rcRootNitrogen);
    fprintf (output_file, "%-7.4lf\t", Crop->rcGrainNitrogenYield);
    fprintf (output_file, "%-7.3lf\t", Crop->rcForageNitrogenYield);
    fprintf (output_file, "%-7.3lf\t", Crop->rcNitrogenCumulative);
    fprintf (output_file, "\n");

    fflush (output_file);
    fclose (output_file);
}
