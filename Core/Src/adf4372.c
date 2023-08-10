#include "adf4372.h"

uint8_t ace_reg_address[72]=
{
    0x0000,
    0x0001,
    0x0002,
    0x0004,
    0x0005,
    0x0006,
    0x000C,
    0x000D,
    0x0010,
    0x0011,
    0x0012,
    0x0014,
    0x0015,
    0x0016,
    0x0017,
    0x0018,
    0x0019,
    0x001A,
    0x001B,
    0x001C,
    0x001D,
    0x001E,
    0x001F,
    0x0020,
    0x0021,
    0x0022,
    0x0023,
    0x0024,
    0x0025,
    0x0026,
    0x0027,
    0x0028,
    0x002A,
    0x002B,
    0x002C,
    0x002D,
    0x002E,
    0x002F,
    0x0030,
    0x0031,
    0x0032,
    0x0033,
    0x0034,
    0x0035,
    0x0036,
    0x0037,
    0x0038,
    0x0039,
    0x003A,
    0x003D,
    0x003E,
    0x003F,
    0x0040,
    0x0041,
    0x0042,
    0x0043,
    0x0044,
    0x0045,
    0x0046,
    0x0047,
    0x0052,
    0x006C,
    0x006E,
    0x006F,
    0x0070,
    0x0071,
    0x0072,
    0x0073,
    0x0079,
    0x007A,
    0x007B,
    0x007C
};

uint8_t ace_reg_map[72]=
{
0x18
,0x80
,0x00
,0x00
,0x00
,0x00
,0x00
,0x00
,0x35//0x36
,0x00
,0x40
,0xcc//0x00
,0xcc//0x00
,0xcc//0x00
,0x81//0x00
,0x3e//0x00
,0x10
,0x27
,0x00
,0x00
,0x00
,0xF8
,0x01
,0x1C
,0x00
,0x00
,0x02
,0x80
,0x0B
,0x6C
,0xDD
,0x03
,0x00
,0x10
,0x44
,0x11
,0x10
,0x92
,0x32
,0xFF
,0x05
,0x03
,0x86
,0xF9
,0x30
,0x00
,0x00
,0x07
,0x55
,0x00
,0x0C
,0x080
,0x50
,0x28
,0x00
,0x00
,0x00
,0x00
,0x00
,0xC0
,0xF4
,0x00
,0x00
,0x00
,0x83
,0x60
,0x02
,0x00
,0x00
,0x00
,0x00
,0x00

};

// uint8_t ace_reg_map[72]= //ace 11.5ghz
// {
// 0x18,
// 0x00,
// 0x00,
// 0x00,
// 0x00,
// 0x00,
// 0x00,
// 0x00,
// 0x39,
// 0x00,
// 0x40,
// 0x099,
// 0x099,
// 0x099,
// 0x06,
// 0x00,
// 0x05,
// 0x00,
// 0x00,
// 0x00,
// 0x00,
// 0x0F8,
// 0x01,
// 0x14,
// 0x00,
// 0x00,
// 0x00,
// 0x080,
// 0x0B,
// 0x68,
// 0x0CD,
// 0x083,
// 0x00,
// 0x10,
// 0x44,
// 0x11,
// 0x12,
// 0x094,
// 0x2A,
// 0x02,
// 0x04,
// 0x22,
// 0x085,
// 0x4C,
// 0x30,
// 0x00,
// 0x00,
// 0x07,
// 0x55,
// 0x00,
// 0x0C,
// 0x080,
// 0x50,
// 0x28,
// 0x00,
// 0x00,
// 0x00,
// 0x00,
// 0x00,
// 0x0C0,
// 0x0F4,
// 0x00,
// 0x00,
// 0x00,
// 0x083,
// 0x32,
// 0x00,
// 0x00,
// 0x00,
// 0x00,
// 0x00
// };

void adf4372_write_single_reg(adf4372_type_def *adf4372_x, uint16_t reg_address, uint8_t reg_value)
{
    SoftSPI_ClrSS(adf4372_x->SoftSPIx);
    SoftSPI_Write_Word(adf4372_x->SoftSPIx,reg_address);
    SoftSPI_Write_Byte(adf4372_x->SoftSPIx,reg_value);
    SoftSPI_SetSS(adf4372_x->SoftSPIx);

}

void adf4372_init(adf4372_type_def *adf4372_x)
{
    for(uint8_t i=0;i<0x7C;i++)
    {
       adf4372_x->adf4372_reg_type[i]=REG_RESERVED;
       adf4372_x->adf4372_reg_value[i]=REG_RESERVED_VALUE;
    }   

    adf4372_x->adf4372_reg_type[0x00]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x00]=SDO_DISABLE|ADDRESS_DESENDING|MSD_FIRST;

    adf4372_x->adf4372_reg_type[0x01]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x01]=SINGLE_INSTRUCTION_MODE;

    adf4372_x->adf4372_reg_type[0x03]=REG_READ;
    adf4372_x->adf4372_reg_value[0x03]=REG_VALUE_NOT_CARE;

    adf4372_x->adf4372_reg_type[0x04]=REG_READ;
    adf4372_x->adf4372_reg_value[0x04]=REG_VALUE_NOT_CARE;

    adf4372_x->adf4372_reg_type[0x05]=REG_READ;
    adf4372_x->adf4372_reg_value[0x05]=REG_VALUE_NOT_CARE;

    adf4372_x->adf4372_reg_type[0x06]=REG_READ;
    adf4372_x->adf4372_reg_value[0x06]=REG_VALUE_NOT_CARE;

    adf4372_x->adf4372_reg_type[0x10]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x10]=INTEGER_WORD_DEFAULT_LSB;

    adf4372_x->adf4372_reg_type[0x11]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x11]=INTEGER_WORD_DEFAULT_MSB;

    adf4372_x->adf4372_reg_type[0x12]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x12]=AUTOCALIBRATION_ENABLE|N_DIVIDER_PRESCALER_4_5;

    adf4372_x->adf4372_reg_type[0x14]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x14]=FRAC1WORD_BIT_7_0_DEFAULT;

    adf4372_x->adf4372_reg_type[0x15]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x15]=FRAC1WORD_BIT_15_8_DEFAULT;

    adf4372_x->adf4372_reg_type[0x16]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x16]=FRAC1WORD_BIT_23_16_DEFAULT;

    adf4372_x->adf4372_reg_type[0x17]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x17]=FRAC1WORD_BIT_24_DEFAULT|FRAC2WORD_BIT_6_0_DEFAULT;

    adf4372_x->adf4372_reg_type[0x18]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x18]=FRAC2WORD_BIT_13_7_DEFAULT;

    adf4372_x->adf4372_reg_type[0x19]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x19]=MOD2WORD_7_0_DEFAULT;

    adf4372_x->adf4372_reg_type[0x1a]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x1a]=PHASE_ADJUST_DISABLE|MOD2WORD_13_8_DEFAULT;

    adf4372_x->adf4372_reg_type[0x1b]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x1b]=PHASE_WORD_BIT_7_0_DEFAULT;

    adf4372_x->adf4372_reg_type[0x1c]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x1c]=PHASE_WORD_BIT_15_8_DEFAULT;

    adf4372_x->adf4372_reg_type[0x1d]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x1d]=PHASE_WORD_BIT_23_16_DEFAULT;

    adf4372_x->adf4372_reg_type[0x1e]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x1e]=CP_CURRENT_5_60_MA|PD_POL_POSITIVE;

    adf4372_x->adf4372_reg_type[0x1f]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x1f]=R_WORD_1;

    adf4372_x->adf4372_reg_type[0x20]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x20]=MUXOUT_DIGITAL_LOCK_DETECT|MUXOUT_ENABLE|MUXOUT_LEVEL_3V3;

    adf4372_x->adf4372_reg_type[0x22]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x22]=REFIN_SINGLE_ENDED|REF_DOUBLER_DISABLE|REF_DIVIDED_BY_2_DISABLE;

    adf4372_x->adf4372_reg_type[0x23]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x23]=TRACKING_FILTER_SET_MAMUAL;

    adf4372_x->adf4372_reg_type[0x24]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x24]=N_COUNTER_FUNDAMENTAL_FEEDBACK|RF_DIV_SEL_1;

    adf4372_x->adf4372_reg_type[0x25]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x25]=RF_DOUBLER_ON|RF_8P_8N_DISABLE|RF_OUT_POWER_NEGATIVE_1;

    adf4372_x->adf4372_reg_type[0x26]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x26]=BLEED_CURRENT_DEFAULT;

    adf4372_x->adf4372_reg_type[0x27]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x27]=LOCK_DETECT_BIAS_12_NS|LOCK_DETECT_PRECISION_FRAC_MODE|GATE_BLEED_ENABLE|NEGATIVE_BLEED_ENABLE|VCO_LDO_DISABLE|RF_PBS_RESERVED;

    adf4372_x->adf4372_reg_type[0x28]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x28]=LOCK_DETECTOR_COUNT_2048_CYCLES|LOSS_OF_LOCK_ENABLE;

    adf4372_x->adf4372_reg_type[0x2a]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x2a]=NEGATIVE_BLEED|READBACK_DATA;

    adf4372_x->adf4372_reg_type[0x2b]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x2b]=AUXILIARY_SDM_ENABLE|MASK_SD_RESET_DISABLE|SD_ENABLE;

    adf4372_x->adf4372_reg_type[0x2c]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x2c]=ALC_RECTIFIER_BIAS_VCO_5V_CORE_D|ALC_THRESHOLD_VCO_5V_CORE_D|VCO_ALC_THRESHOLD_CORE_D|TEMP_DEPENDENT_VCO_CALIBRATION_DISABLE|ALC_ENABLE;

    adf4372_x->adf4372_reg_type[0x2d]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x2d]=ALC_RECTIFIER_BIAS_VCO_5V_CORE_C|ALC_THRESHOLD_VCO_5V_CORE_C|VCO_ALC_THRESHOLD_VCO_5V_CORE_C;

    adf4372_x->adf4372_reg_type[0x2e]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x2e]=ALC_RECTIFIER_BIAS_VCO_5V_CORE_B|ALC_THRESHOLD_VCO_5V_CORE_B|VCO_ALC_THRESHOLD_VCO_5V_CORE_B;

    adf4372_x->adf4372_reg_type[0x2f]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x2f]=LDO_VCO_5V|ALC_RECTIFIER_BIAS_VCO_5V_CORE_A|ALC_THRESHOLD_VCO_5V_CORE_A|VCO_ALC_THRESHOLD_VCO_CORE_A;   

    adf4372_x->adf4372_reg_type[0x30]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x30]=VCO_BAND_DIV_DEFAULT;    

    adf4372_x->adf4372_reg_type[0x31]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x31]=TIMEOUT_BIT_7_0_DEFAULT; 

    adf4372_x->adf4372_reg_type[0x32]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x32]=ADC_INPUT_MUX_PTAT|ADC_FAST_CONVERSION_DISABLE|ADC_CONTINUOUS_CONVERSION_DISABLE|ADC_ENABLE|TIMEOUT_BIT_9_8_DEFAULT;    

    adf4372_x->adf4372_reg_type[0x33]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x33]=SYNTH_LOCK_TIMEOUT_DEFAULT; 

    adf4372_x->adf4372_reg_type[0x34]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x34]=VCO_FSM_TEST_MODES_DEFAULT|VCO_ALC_TIMEOUT_DEFAULT; 

    adf4372_x->adf4372_reg_type[0x35]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x35]=ADC_CLK_DIVIDER_DEFAULT;    

    adf4372_x->adf4372_reg_type[0x36]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x36]=ICP_ADJUST_OFFSET_RESERVED;    

    adf4372_x->adf4372_reg_type[0x37]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x37]=TEST_MODE_SELECT_BAND_IN_CORE_DEFAULT;

    adf4372_x->adf4372_reg_type[0x38]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x38]=TEST_MODE_SELECT_CORE_DEFAULT|TEST_MODE_SELECT_VCO_BIAS_DEFAULT;

    adf4372_x->adf4372_reg_type[0x39]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x39]=TEST_MODE_VCO_MUX_BUSY|TEST_MODE_VCO_TARGET_VOLTAGE_DEFAULT;   

    adf4372_x->adf4372_reg_type[0x3a]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x3a]=ADC_OFFSET_DEFAULT;

    adf4372_x->adf4372_reg_type[0x3d]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x3d]=SD_RESET_RESERVED;   

    adf4372_x->adf4372_reg_type[0x3e]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x3e]=CP_TEST_MODE_NORMAL_OPERATION; 

    adf4372_x->adf4372_reg_type[0x3f]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x3f]=REG003F_RESERVED;

    adf4372_x->adf4372_reg_type[0x40]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x40]=REG0040_RESERVED;

    adf4372_x->adf4372_reg_type[0x41]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x41]=REG0041_RESERVED;

    adf4372_x->adf4372_reg_type[0x47]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x47]=REG0047_RESERVED;

    adf4372_x->adf4372_reg_type[0x52]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x52]=REG0052_RESERVED;

    adf4372_x->adf4372_reg_type[0x6e]=REG_READ;
    adf4372_x->adf4372_reg_value[0x6e]=REG_VALUE_NOT_CARE;

    adf4372_x->adf4372_reg_type[0x6f]=REG_READ;
    adf4372_x->adf4372_reg_value[0x6f]=REG_VALUE_NOT_CARE;

    adf4372_x->adf4372_reg_type[0x70]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x70]=BAND_SEL_X2_DEFAULT|BIAS_SEL_X2_DEFAULT;

    adf4372_x->adf4372_reg_type[0x71]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x71]=BAND_SEL_X4_NOT_USED|BIAS_SEL_X4_NOT_USED;    

    adf4372_x->adf4372_reg_type[0x72]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x72]=AUX_FREQ_SEL_DEVIDED_OUTPUT|POUT_AUX_DEFAULT|PDB_AUX_RF_OFF|COUPLED_VCO_RESERVED; 

    adf4372_x->adf4372_reg_type[0x73]=REG_WRITE;
    adf4372_x->adf4372_reg_value[0x73]=REG_RESERVED;

    adf4372_x->adf4372_reg_type[0x7c]=REG_READ;
    adf4372_x->adf4372_reg_value[0x7c]=REG_VALUE_NOT_CARE;


    SoftSPI_ClrSS(adf4372_x->SoftSPIx);
    SoftSPI_Write_Mem(adf4372_x->SoftSPIx,0x00,&adf4372_x->adf4372_reg_value[0x00],1,1);
    SoftSPI_SetSS(adf4372_x->SoftSPIx);

    HAL_Delay(100);

    SoftSPI_ClrSS(adf4372_x->SoftSPIx);
    SoftSPI_Write_Mem(adf4372_x->SoftSPIx,0x01,&adf4372_x->adf4372_reg_value[0x01],1,1);
    SoftSPI_SetSS(adf4372_x->SoftSPIx);

    // stream mode
    // SoftSPI_ClrSS(adf4372_x->SoftSPIx);
    // SoftSPI_Write_Mem(adf4372_x->SoftSPIx,0x7c,&adf4372_x->adf4372_reg_value[0x7c],0x7c-0x10,0);
    // SoftSPI_SetSS(adf4372_x->SoftSPIx);

    // single struction mode
    for(uint8_t i=0;i<(0x7c-0x10+1);i++)
    {
        if(adf4372_x->adf4372_reg_type[0x7c-i]==REG_WRITE)
        adf4372_write_single_reg(adf4372_x,0x7c-i,adf4372_x->adf4372_reg_value[0x7c-i]);
    }
}

void adf4372_update_freq(adf4372_type_def *adf4372_x, uint8_t rf_int,uint8_t rf_frac)
{   
    double n;
    double n_frac;
    double remainder;
    uint32_t inte;
    uint32_t frac1;
    uint32_t frac2;
    uint32_t mod2;
    uint8_t bleed_current;
	
    n=(rf_int+((double)rf_frac)/100)/2*10;

    inte=(uint16_t)n;
    frac1=(n-(uint16_t)n)*33554432; //30198988
    remainder=(n-(uint16_t)n)*33554432-frac1; //0.8
    mod2=10000;
    frac2=mod2*remainder+1; //8000

    bleed_current=4*5600/n/3.75;

    adf4372_x->adf4372_reg_value[0x26]=bleed_current;

    if(rf_frac%20==0)
        adf4372_x->adf4372_reg_value[0x2b]=0x11;
    else
        adf4372_x->adf4372_reg_value[0x2b]=0x10;

    adf4372_x->adf4372_reg_value[0x1f]=0x01;
    adf4372_x->adf4372_reg_value[0x1e]=0xF8;
    adf4372_x->adf4372_reg_value[0x1d]=0x00;
    adf4372_x->adf4372_reg_value[0x1c]=0x00;
    adf4372_x->adf4372_reg_value[0x1b]=0x00;
    adf4372_x->adf4372_reg_value[0x1a]=(adf4372_x->adf4372_reg_value[0x1a]&0xC0)|((mod2>>8)&0x3f);
    adf4372_x->adf4372_reg_value[0x19]=mod2;
    adf4372_x->adf4372_reg_value[0x18]=(adf4372_x->adf4372_reg_value[0x18]&0x80)|((frac2>>7)&0x7f);
    adf4372_x->adf4372_reg_value[0x17]=(frac2<<1)|(frac1>>24);
    adf4372_x->adf4372_reg_value[0x16]=frac1>>16;
    adf4372_x->adf4372_reg_value[0x15]=frac1>>8;
    adf4372_x->adf4372_reg_value[0x14]=frac1;
    adf4372_x->adf4372_reg_value[0x11]=inte>>8;
    adf4372_x->adf4372_reg_value[0x10]=inte;

    adf4372_write_single_reg(adf4372_x,0x2b, adf4372_x->adf4372_reg_value[0x2b]);
    adf4372_write_single_reg(adf4372_x,0x26, adf4372_x->adf4372_reg_value[0x26]);
    adf4372_write_single_reg(adf4372_x,0x1f, adf4372_x->adf4372_reg_value[0x1f]);
    adf4372_write_single_reg(adf4372_x,0x1a, adf4372_x->adf4372_reg_value[0x1a]);
    adf4372_write_single_reg(adf4372_x,0x19, adf4372_x->adf4372_reg_value[0x19]);
    adf4372_write_single_reg(adf4372_x,0x18, adf4372_x->adf4372_reg_value[0x18]);
    adf4372_write_single_reg(adf4372_x,0x17, adf4372_x->adf4372_reg_value[0x17]);
    adf4372_write_single_reg(adf4372_x,0x16, adf4372_x->adf4372_reg_value[0x16]);
    adf4372_write_single_reg(adf4372_x,0x15, adf4372_x->adf4372_reg_value[0x15]);
    adf4372_write_single_reg(adf4372_x,0x14, adf4372_x->adf4372_reg_value[0x14]);
    adf4372_write_single_reg(adf4372_x,0x11, adf4372_x->adf4372_reg_value[0x11]);
    adf4372_write_single_reg(adf4372_x,0x10, adf4372_x->adf4372_reg_value[0x10]);

    // stream mode
    // SoftSPI_ClrSS(adf4372_x->SoftSPIx);
    // SoftSPI_Write_Mem(adf4372_x->SoftSPIx,0x1f,&adf4372_x->adf4372_reg_value[0x1f],16,0);
    // SoftSPI_SetSS(adf4372_x->SoftSPIx);

    // single struction mode
    // for(uint8_t i=0x1f;i>0x0f;i--)
    // {
    //     // if(adf4372_x->adf4372_reg_type[i]==REG_WRITE)
    //         adf4372_write_single_reg(adf4372_x,i,adf4372_x->adf4372_reg_value[i]);
    // }
}

void adf4372_update_freq_125_fpfd(adf4372_type_def *adf4372_x)
{
    ;
}

void adf4372_ace_init(adf4372_type_def *adf4372_x)
{
    adf4372_write_single_reg(adf4372_x,0x00,0x00);

    HAL_Delay(100);
    
    adf4372_write_single_reg(adf4372_x,0x01,0x80);

    HAL_Delay(100);
    
    for(uint8_t i=72;i>7;i--)
    {
        adf4372_write_single_reg(adf4372_x,ace_reg_address[i],ace_reg_map[i]);
    }
}

void adf4372_ace_update_freq(adf4372_type_def *adf4372_x)
{
    for(uint8_t i=22;i>7;i--)
    {
        adf4372_write_single_reg(adf4372_x,ace_reg_address[i],ace_reg_map[i]);
    }
    // adf4372_write_single_reg(adf4372_x,0x1f,0x01);
    // adf4372_write_single_reg(adf4372_x,0x1a,0x03);
    // adf4372_write_single_reg(adf4372_x,0x19,0xe8);
    // adf4372_write_single_reg(adf4372_x,0x18,0x00);
    // adf4372_write_single_reg(adf4372_x,0x17,0x00);
    // adf4372_write_single_reg(adf4372_x,0x16,0x00);
    // adf4372_write_single_reg(adf4372_x,0x15,0x00);
    // adf4372_write_single_reg(adf4372_x,0x14,0x00);
    // adf4372_write_single_reg(adf4372_x,0x11,0x00);
    // adf4372_write_single_reg(adf4372_x,0x10,0x32);
}

void freq_write_flash(uint32_t rf_int,uint32_t rf_frac)
{
    uint32_t __addr;
    uint32_t PageError = 0;

    FLASH_EraseInitTypeDef EraseInitStruct;

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress=FLASH_USER_START_ADDR; /* start @ of user flash area */
    EraseInitStruct.NbPages=1;

    HAL_FLASH_Unlock();
    HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

    __addr=FLASH_USER_START_ADDR;
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, __addr,rf_int);

    __addr+=4;
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, __addr,rf_frac);

    HAL_FLASH_Lock(); 
}
