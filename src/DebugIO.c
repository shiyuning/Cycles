#include "Cycles.h"

void PrintSimContrl (ctrl_struct SimControl)
{
    printf ("\n*Simulation Control:\n");
    printf ("*%-22s\t%-4d\n", "Simulation Start Year", SimControl.simStartYear);
    printf ("*%-22s\t%-4d\n", "Simulation End Year", SimControl.simEndYear);
    printf ("*%-22s\t%-4d\n", "Simulation Total Years", SimControl.totalYears);
    printf ("*%-22s\t%-4d\n", "Hourly Infiltration", SimControl.hourlyInfiltration);
    printf ("*%-22s\t%-4d\n", "Daily Weather Out", SimControl.weatherDailyOutput);
    printf ("*%-22s\t%-4d\n", "Daily Crop Out", SimControl.cropDailyOutput);
    printf ("*%-22s\t%-4d\n", "Daily Residue", SimControl.residueDailyOutput);
    printf ("*%-22s\t%-4d\n", "Daily Water Out", SimControl.waterDailyOutput);
    printf ("*%-22s\t%-4d\n", "Daily Nitrogen Out", SimControl.nitrogenDailyOutput);
    printf ("*%-22s\t%-4d\n", "Daily Soil Carbon Out", SimControl.soilCarbonDailyOutput);
    printf ("*%-22s\t%-4d\n", "Daily Soil Out", SimControl.soilDailyOutput);
    printf ("*%-22s\t%-4d\n", "Annual Soil Out", SimControl.annualSoilOutput);
    printf ("*%-22s\t%-4d\n", "Annual Profile Out", SimControl.profileOutput);
    printf ("*%-22s\t%-4d\n", "Season_Out", SimControl.seasonOutput);
    printf ("\n");
}

void PrintSoil (soil_struct Soil)
{
    int             i;

    printf ("\n*Soil Description:\n");
    printf ("*%-12s\t%-5.2lf\n", "Curve number", Soil.Curve_Number);
    printf ("*%-12s\t%-4.2lf\n", "Slope", Soil.Percent_Slope);
    printf ("*%-12s\t%-3d\n", "Total layers", Soil.totalLayers);
    printf ("*%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "Layer", "Thickness", "Clay", "Sand", "Organic", "Buld Dens", "Field Cpct", "Wilt Pnt", "NO3", "CH4");
    for (i = 0; i < Soil.totalLayers; i++)
        printf ("*%-10d\t%-10.2lf\t%-10.2lf\t%-10.2lf\t%-10.2lf\t%-10.2lf\t%-10.2lf\t%-10.2lf\t%-10.2lf\t%-10.2lf\n", i + 1, Soil.layerThickness[i], Soil.Clay[i], Soil.Sand[i], Soil.IOM[i], Soil.BD[i], Soil.FC[i], Soil.PWP[i], Soil.NO3[i], Soil.NH4[i]);
    printf ("\n");
}

void PrintCrop (comm_struct Community)
{
    int             i;

    printf ("\n\n*Crop description file contains descriptions of %d crop types.\n\n", Community.NumCrop);

    for (i = 0; i < Community.NumCrop; i++)
    {
        printf ("*%-38s\t%-10s\n", "NAME", Community.Crop[i].cropName);
        printf ("*%-38s\t%-7.2lf\n", "FLOWERING_TT", Community.Crop[i].userFloweringTT);
        printf ("*%-38s\t%-7.2lf\n", "MATURITY TT", Community.Crop[i].userMaturityTT);
        printf ("*%-38s\t%-9.2lf\n", "MAXIMUM_SOIL_COVERAGE", Community.Crop[i].userMaximumSoilCoverage);
        printf ("*%-38s\t%-9.2lf\n", "MAXIMUM_ROOTING_DEPTH", Community.Crop[i].userMaximumRootingDepth);
        printf ("*%-38s\t%-9.2lf\n", "AVERAGE_EXPECTED_YIELD", Community.Crop[i].userExpectedYieldAvg);
        printf ("*%-38s\t%-9.2lf\n", "MAXIMUM_EXPECTED_YIELD", Community.Crop[i].userExpectedYieldMax);
        printf ("*%-38s\t%-9.2lf\n", "MINIMUM_EXPECTED_YIELD", Community.Crop[i].userExpectedYieldMin);
        printf ("*%-38s\t%-9.2lf\n", "COMMERCIAL_YIELD_MOISTURE", Community.Crop[i].userPercentMoistureInYield);
        printf ("*%-38s\t%-9.2lf\n", "STANDING_RESIDUE_AT_HARVEST", Community.Crop[i].userFractionResidueStanding);
        printf ("*%-38s\t%-9.2lf\n", "RESIDUE_REMOVED", Community.Crop[i].userFractionResidueRemoved);
        printf ("*%-38s\t%-9.2lf\n", "HARVEST_TIMING", Community.Crop[i].userClippingTiming);
        printf ("*%-38s\t%-9.2lf\n", "MIN_TEMPERATURE_FOR_TRANSPIRATION", Community.Crop[i].userTranspirationMinTemperature);
        printf ("*%-38s\t%-9.2lf\n", "THRESHOLD_TEMPERATURE_FOR_TRANPIRATION", Community.Crop[i].userTranspirationThresholdTemperature);
        printf ("*%-38s\t%-9.2lf\n", "MIN_TEMPERATURE_FOR_COLD_DAMAGE", Community.Crop[i].userColdDamageMinTemperature);
        printf ("*%-38s\t%-9.2lf\n", "THRESHOLD_TEMPERATURE_FOR_COLD_DAMAGE", Community.Crop[i].userColdDamageThresholdTemperature);
        printf ("*%-38s\t%-9.2lf\n", "BASE_TEMPERATURE_FOR_DEVELOPMENT", Community.Crop[i].userTemperatureBase);
        printf ("*%-38s\t%-9.2lf\n", "OPTIMUM_TEMPERATURE_FOR_DEVELOPEMENT", Community.Crop[i].userTemperatureOptimum);
        printf ("*%-38s\t%-9.2lf\n", "MAX_TEMPERATURE_FOR_DEVELOPMENT", Community.Crop[i].userTemperatureMaximum);
        printf ("*%-38s\t%-9.2lf\n", "INITIAL_PARTITIONING_TO_SHOOT", Community.Crop[i].userShootPartitionInitial);
        printf ("*%-38s\t%-9.2lf\n", "FINAL_PARTITIONING_TO_SHOOT", Community.Crop[i].userShootPartitionFinal);
        printf ("*%-38s\t%-9.2lf\n", "RAIDATION_USE_EFFICIENCY", Community.Crop[i].userRadiationUseEfficiency);
        printf ("*%-38s\t%-9.2lf\n", "TRANSPIRATION_USE_EFFICIENCY", Community.Crop[i].userTranspirationUseEfficiency);
        printf ("*%-38s\t%-9.2lf\n", "MAXIMUM_HARVEST_INDEX", Community.Crop[i].userHIx);
        printf ("*%-38s\t%-9.2lf\n", "MINIMUM_HARVEST_INDEX", Community.Crop[i].userHIo);
        printf ("*%-38s\t%-9.2lf\n", "HARVEST_INDEX", Community.Crop[i].userHIk);
        printf ("*%-38s\t%-9.2lf\n", "THERMAL_TIME_TO_EMERGENCE", Community.Crop[i].userEmergenceTT);
        printf ("*%-38s\t%-9.2lf\n", "N_MAX_CONCENTRATION", Community.Crop[i].userNMaxConcentration);
        printf ("*%-38s\t%-9.2lf\n", "N_DILUTION_SLOPE", Community.Crop[i].userNDilutionSlope);
        printf ("*%-38s\t%-9.2lf\n", "KC", Community.Crop[i].userKc);
        printf ("*%-38s\t%-3d\n", "ANNUAL", Community.Crop[i].userAnnual);
        printf ("*%-38s\t%-3d\n", "LEGUME", Community.Crop[i].userLegume);
        printf ("*%-38s\t%-3d\n\n", "C3", Community.Crop[i].userC3orC4);
    }
    printf ("\n");
}

void PrintOperation (plant_struct *plantedCrops, int NumPlanting, tillage_struct *Tillage, int NumTillage, fixirr_struct *FixedIrrigation, int NumIrrigation, fixfert_struct *FixedFertilization, int NumFertilization)
{
    int             i;
    tillage_struct *tillage;
    fixirr_struct  *fixirr;
    fixfert_struct *fixfert;

    printf ("\n*Planting:\n");
    for (i = 0; i < NumPlanting; i++)
    {
        printf ("*%-18s\t%-3d\n", "YEAR", plantedCrops[i].opYear);
        printf ("*%-18s\t%-3d\n", "DOY", plantedCrops[i].opDay);
        printf ("*%-18s\t%-10s\n", "CROP", plantedCrops[i].cropName);
        printf ("*%-18s\t%-3d\n", "AUTO IRRIGATION", plantedCrops[i].usesAutoIrrigation);
        printf ("*%-18s\t%-3d\n", "AUTO FERTILIAZTION", plantedCrops[i].usesAutoFertilization);
        printf ("*%-18s\t%-3d\n\n", "PLANT ID", plantedCrops[i].plantID);
    }
    printf ("\n");

    printf ("*Tillage:\n");
    for (i = 0; i < NumTillage; i++)
    {
        tillage = &Tillage[i];
        printf ("*%-18s\t%-3d\n", "YEAR", tillage->opYear);
        printf ("*%-18s\t%-3d\n", "DOY", tillage->opDay);
        printf ("*%-18s\t%-128s\n", "TOOL", tillage->opToolName);
        printf ("*%-18s\t%-4.2lf\n", "DEPTH", tillage->opDepth);
        printf ("*%-18s\t%-4.2lf\n", "SOIL DISTURB RATIO", tillage->opSDR);
        printf ("*%-18s\t%-4.2lf\n\n", "MIXING EFFICIENCY", tillage->opMixingEfficiency);
    }
    printf ("\n");

    printf ("*Fixed Irrigation:\n");
    for (i = 0; i < NumIrrigation; i++)
    {
        fixirr = &FixedIrrigation[i];
        printf ("*%-18s\t%-3d\n", "YEAR", fixirr->opYear);
        printf ("*%-18s\t%-3d\n", "DOY", fixirr->opDay);
        printf ("*%-18s\t%-4.2lf\n\n", "VOLUME", fixirr->opVolume);
    }
    printf ("\n");

    printf ("*Fixed Fertilization:\n");
    for (i = 0; i < NumFertilization; i++)
    {
        fixfert = &FixedFertilization[i];
        printf ("*%-18s\t%-3d\n", "YEAR", fixfert->opYear);
        printf ("*%-18s\t%-3d\n", "DOY", fixfert->opDay);
        printf ("*%-18s\t%-128s\n", "SOURCE", fixfert->opSource);
        printf ("*%-18s\t%-6.2lf\n", "MASS", fixfert->opMass);
        printf ("*%-18s\t%-128s\n", "FORM", fixfert->opForm);
        printf ("*%-18s\t%-128s\n", "METHOD", fixfert->opMethod);
        printf ("*%-18s\t%-3d\n", "DEPTH", fixfert->opLayer);
        printf ("*%-18s\t%-6.2lf\n", "C_ORGANIC", fixfert->opC_Organic);
        printf ("*%-18s\t%-6.2lf\n", "C_CHARCOAL", fixfert->opC_Charcoal);
        printf ("*%-18s\t%-6.2lf\n", "N_ORGANIC", fixfert->opN_Organic);
        printf ("*%-18s\t%-6.2lf\n", "N_CHARCOAL", fixfert->opN_Charcoal);
        printf ("*%-18s\t%-6.2lf\n", "N_NH4", fixfert->opN_NH4);
        printf ("*%-18s\t%-6.2lf\n", "N_NO3", fixfert->opN_NO3);
        printf ("*%-18s\t%-6.2lf\n", "P_ORGANIC", fixfert->opP_Organic);
        printf ("*%-18s\t%-6.2lf\n", "P_CHARCOOAL", fixfert->opP_Charcoal);
        printf ("*%-18s\t%-6.2lf\n", "P_INORGANIC", fixfert->opP_Inorganic);
        printf ("*%-18s\t%-6.2lf\n", "K", fixfert->opK);
        printf ("*%-18s\t%-6.2lf\n\n", "S", fixfert->opS);
    }
    printf ("\n");
}

void PrintWeather (weather_struct Weather)
{
    printf ("\n*Weather:\n");
    printf ("*%-16s\t%-6.2lf\n", "LATITUDE", Weather.siteLatitude);
    printf ("*%-16s\t%-6.2lf\n", "ALTITUDE", Weather.siteAltitude);
    printf ("*%-16s\t%-6.2lf\n", "SCREENING_HEIGHT", Weather.screeningHeight);
    printf ("\n");
}
