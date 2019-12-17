
#include "DrvLCD.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_hal.h"


uint16_t DeviceCode;

void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
    /* Write 16-bit Index, then Write Reg */
    LCD->LCD_REG = LCD_Reg;
    /* Write 16-bit Reg */
    LCD->LCD_RAM = LCD_RegValue;
}


void LCD_WriteRAM(uint16_t RGB_Code)
{
	/* Write 16-bit GRAM Reg */
	LCD->LCD_RAM = RGB_Code;
}


uint16_t LCD_ReadRAM(void)
{
	/* Write 16-bit Index (then Read Reg) */
	LCD->LCD_REG = LCD_REG_34; /* Select GRAM Reg */
	/* Read 16-bit Reg */
	return LCD->LCD_RAM;
}


void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	if(DeviceCode==0x8989)
	{
		//LCD_WriteReg(0x004e,Xpos);
		//LCD_WriteReg(0x004f,Ypos);
		LCD_WriteReg(0x004F,Xpos);
		LCD_WriteReg(0x004E,Ypos);
	}
	else if(DeviceCode==0x9325)
	{
		LCD_WriteReg(0x0020,Xpos);
		LCD_WriteReg(0x0021,0x13f-Ypos);
	}
	else
	{
		LCD_WriteReg(0x0020,Ypos);
		LCD_WriteReg(0x0021,0x13f-Xpos);
	}
	//LCD_WriteReg(LCD_REG_32, Xpos);
	//LCD_WriteReg(LCD_REG_33, Ypos);
}


void LCD_WriteRAM_Prepare(void)
{
    LCD->LCD_REG = LCD_REG_34;
}


void LCD_Clear(uint16_t Color)
{
    uint32_t index = 0;
    
    //LCD_SetCursor(0x00, 0x013F);
    
    LCD_SetCursor(0, 0);
    LCD_WriteRAM_Prepare();
    for(index = 0; index < 320*240; index++)
    {
        LCD->LCD_RAM = Color;
    }
}


void LCD_Draw(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t *pColor)
{
    uint16_t draw_x, draw_y;
    uint16_t start_x,start_y,end_x,end_y;
    
    if(xStart < xEnd) {
        start_x = xStart;
        end_x = xEnd;
    }
    else {
        start_x = xEnd;
        end_x = xStart;
    }
    if(yStart < yEnd) {
        start_y = yStart;
        end_y = yEnd;
    }
    else {
        start_y = yEnd;
        end_y = yStart;
    }
    
    for(draw_y = start_y; draw_y <= end_y; draw_y++) {
        LCD_SetCursor(start_x, draw_y);
        LCD_WriteRAM_Prepare();
        for(draw_x = start_x; draw_x <= end_x; draw_x++) {
            LCD->LCD_RAM = *pColor;
            pColor++;
        }
    }
}


uint16_t LCD_ReadReg(uint8_t LCD_Reg)
{
    /* Write 16-bit Index (then Read Reg) */
    LCD->LCD_REG = LCD_Reg;
    /* Read 16-bit Reg */
    return (LCD->LCD_RAM);
}


void LCD_Init(void)
{
    volatile uint32_t lcdid = 0;
    volatile uint32_t test = 0;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    
    lcdid = LCD_ReadReg(0x00);  /* Read the LCD ID */
    
    if( (0 == lcdid) || (0x0FFF > lcdid) || ( (lcdid != 0x8989) && (lcdid != 0x9320) && (lcdid != 0x9325)) )
    {
        lcdid =  0x8989;
    }
    DeviceCode = lcdid;
    
    /* Check if the LCD is ILI9320 Controller */
    if(lcdid == 0x9320)
    {
        /* Start Initial Sequence ------------------------------------------------*/
        LCD_WriteReg(LCD_REG_229,0x8000); /* Set the internal vcore voltage */
        LCD_WriteReg(LCD_REG_0,  0x0001); /* Start internal OSC. */
        LCD_WriteReg(LCD_REG_1,  0x0100); /* set SS and SM bit */
        LCD_WriteReg(LCD_REG_2,  0x0700); /* set 1 line inversion */
        LCD_WriteReg(LCD_REG_3,  0x1030); /* set GRAM write direction and BGR=1. */
        LCD_WriteReg(LCD_REG_4,  0x0000); /* Resize register */
        LCD_WriteReg(LCD_REG_8,  0x0202); /* set the back porch and front porch */
        LCD_WriteReg(LCD_REG_9,  0x0000); /* set non-display area refresh cycle ISC[3:0] */
        LCD_WriteReg(LCD_REG_10, 0x0000); /* FMARK function */
        LCD_WriteReg(LCD_REG_12, 0x0000); /* RGB interface setting */
        LCD_WriteReg(LCD_REG_13, 0x0000); /* Frame marker Position */
        LCD_WriteReg(LCD_REG_15, 0x0000); /* RGB interface polarity */
        
        /* Power On sequence -----------------------------------------------------*/
        LCD_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
        LCD_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
        LCD_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
        LCD_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude */
        _delay_(20);                 /* Dis-charge capacitor power voltage (200ms) */
        LCD_WriteReg(LCD_REG_16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
        LCD_WriteReg(LCD_REG_17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
        _delay_(5);                  /* Delay 50 ms */
        LCD_WriteReg(LCD_REG_18, 0x0139); /* VREG1OUT voltage */
        _delay_(5);                  /* Delay 50 ms */
        LCD_WriteReg(LCD_REG_19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
        LCD_WriteReg(LCD_REG_41, 0x0013); /* VCM[4:0] for VCOMH */
        _delay_(5);                  /* Delay 50 ms */
        LCD_WriteReg(LCD_REG_32, 0x0000); /* GRAM horizontal Address */
        LCD_WriteReg(LCD_REG_33, 0x0000); /* GRAM Vertical Address */
        
        /* Adjust the Gamma Curve ------------------------------------------------*/
        LCD_WriteReg(LCD_REG_48, 0x0006);
        LCD_WriteReg(LCD_REG_49, 0x0101);
        LCD_WriteReg(LCD_REG_50, 0x0003);
        LCD_WriteReg(LCD_REG_53, 0x0106);
        LCD_WriteReg(LCD_REG_54, 0x0b02);
        LCD_WriteReg(LCD_REG_55, 0x0302);
        LCD_WriteReg(LCD_REG_56, 0x0707);
        LCD_WriteReg(LCD_REG_57, 0x0007);
        LCD_WriteReg(LCD_REG_60, 0x0600);
        LCD_WriteReg(LCD_REG_61, 0x020b);
        
        /* Set GRAM area ---------------------------------------------------------*/
        LCD_WriteReg(LCD_REG_80, 0x0000); /* Horizontal GRAM Start Address */
        LCD_WriteReg(LCD_REG_81, 0x00EF); /* Horizontal GRAM End Address */
        LCD_WriteReg(LCD_REG_82, 0x0000); /* Vertical GRAM Start Address */
        LCD_WriteReg(LCD_REG_83, 0x013F); /* Vertical GRAM End Address */
        LCD_WriteReg(LCD_REG_96,  0x2700); /* Gate Scan Line */
        LCD_WriteReg(LCD_REG_97,  0x0001); /* NDL,VLE, REV */
        LCD_WriteReg(LCD_REG_106, 0x0000); /* set scrolling line */
        
        /* Partial Display Control -----------------------------------------------*/
        LCD_WriteReg(LCD_REG_128, 0x0000);
        LCD_WriteReg(LCD_REG_129, 0x0000);
        LCD_WriteReg(LCD_REG_130, 0x0000);
        LCD_WriteReg(LCD_REG_131, 0x0000);
        LCD_WriteReg(LCD_REG_132, 0x0000);
        LCD_WriteReg(LCD_REG_133, 0x0000);
        
        /* Panel Control ---------------------------------------------------------*/
        LCD_WriteReg(LCD_REG_144, 0x0010);
        LCD_WriteReg(LCD_REG_146, 0x0000);
        LCD_WriteReg(LCD_REG_147, 0x0003);
        LCD_WriteReg(LCD_REG_149, 0x0110);
        LCD_WriteReg(LCD_REG_151, 0x0000);
        LCD_WriteReg(LCD_REG_152, 0x0000);
        
        /* Set GRAM write direction and BGR = 1 */
        /* I/D=01 (Horizontal : increment, Vertical : decrement) */
        /* AM=1 (address is updated in vertical writing direction) */
        LCD_WriteReg(LCD_REG_3, 0x1018);
        
        LCD_WriteReg(LCD_REG_7, 0x0173); /* 262K color and display ON */  
    }
    
    else if(lcdid==0x8989)
    {
        // power supply setting 
        // set R07h at 0021h (GON=1,DTE=0,D[1:0]=01)
        //LCD_WriteReg(0x0007,0x0021);       
        // set R00h at 0001h (OSCEN=1)       
        LCD_WriteReg(0x0000,0x0001);       
        // set R07h at 0023h (GON=1,DTE=0,D[1:0]=11)       
        // LCD_WriteReg(0x0007,0x0023);       
        // set R10h at 0000h (Exit sleep mode)       
        LCD_WriteReg(0x0010,0x0000);       
        _delay_(5);                  /* Delay 50 ms */      
        // set R07h at 0033h (GON=1,DTE=1,D[1:0]=11)       
        //LCD_WriteReg(0x0007,0x0033);       
        LCD_WriteReg(0x0007,0x0233);       
        // Entry mode setting (R11h)       
        // R11H Entry mode       
        // vsmode DFM1 DFM0 TRANS OEDef WMode DMode1 DMode0 TY1 TY0 ID1 ID0 AM LG2 LG2 LG0       
        //   0     1    1     0     0     0     0      0     0   1   1   1  *   0   0   0       
        //LCD_WriteReg(0x0011,0x6070);       
        LCD_WriteReg(0x0011,0x6078);       
        // LCD driver AC setting (R02h)       
        LCD_WriteReg(0x0002,0x0600);       
        // power control 1       
        // DCT3 DCT2 DCT1 DCT0 BT2 BT1 BT0 0 DC3 DC2 DC1 DC0 AP2 AP1 AP0 0       
        // 1     0    1    0    1   0   0  0  1   0   1   0   0   1   0  0       
        // DCT[3:0] fosc/4 BT[2:0]  DC{3:0] fosc/4       
        LCD_WriteReg(0x0003,0xA8A4);//0x0804  
        LCD_WriteReg(0x000C,0x0000);//
        LCD_WriteReg(0x000D,0x080C);//       
        // power control 4       
        // 0 0 VCOMG VDV4 VDV3 VDV2 VDV1 VDV0 0 0 0 0 0 0 0 0       
        // 0 0   1    0    1    0    1    1   0 0 0 0 0 0 0 0       
        LCD_WriteReg(0x000E,0x2900);       
        LCD_WriteReg(0x001E,0x00B8);       
        LCD_WriteReg(0x0001,0x293F);
        LCD_WriteReg(0x0010,0x0000);       
        LCD_WriteReg(0x0005,0x0000);       
        LCD_WriteReg(0x0006,0x0000);       
        LCD_WriteReg(0x0016,0xEF1C);     
        LCD_WriteReg(0x0017,0x0003);     
        LCD_WriteReg(0x0007,0x0233);		//0x0233       
        LCD_WriteReg(0x000B,0x0000|(3<<6));  //////     
        LCD_WriteReg(0x000F,0x0000);		//扫描开始地址
        LCD_WriteReg(0x0041,0x0000);     
        LCD_WriteReg(0x0042,0x0000);     
        LCD_WriteReg(0x0048,0x0000);     
        LCD_WriteReg(0x0049,0x013F);     
        LCD_WriteReg(0x004A,0x0000);     
        LCD_WriteReg(0x004B,0x0000);     
        LCD_WriteReg(0x0044,0xEF00);     
        LCD_WriteReg(0x0045,0x0000);     
        LCD_WriteReg(0x0046,0x013F);     
        LCD_WriteReg(0x0030,0x0707);     
        LCD_WriteReg(0x0031,0x0204);     
        LCD_WriteReg(0x0032,0x0204);     
        LCD_WriteReg(0x0033,0x0502);     
        LCD_WriteReg(0x0034,0x0507);     
        LCD_WriteReg(0x0035,0x0204);     
        LCD_WriteReg(0x0036,0x0204);     
        LCD_WriteReg(0x0037,0x0502);     
        LCD_WriteReg(0x003A,0x0302);     
        LCD_WriteReg(0x003B,0x0302);     
        LCD_WriteReg(0x0023,0x0000);     
        LCD_WriteReg(0x0024,0x0000);     
        LCD_WriteReg(0x0025,0x8000);     
        LCD_WriteReg(0x004e,0);        //列(X)首址0
        LCD_WriteReg(0x004f,0);        //行(Y)首址0
    }
    else if(lcdid == 0x9325) /* Check if the LCD is ILI9325 Controller */
    {
        /* Start Initial Sequence ------------------------------------------------*/
        LCD_WriteReg(LCD_REG_0, 0x0001); /* Start internal OSC. */
        LCD_WriteReg(LCD_REG_1, 0x0100); /* Set SS and SM bit */
        LCD_WriteReg(LCD_REG_2, 0x0700); /* Set 1 line inversion */
        LCD_WriteReg(LCD_REG_3, 0x1018); /* Set GRAM write direction and BGR=1. */
        LCD_WriteReg(LCD_REG_4, 0x0000); /* Resize register */
        LCD_WriteReg(LCD_REG_8, 0x0202); /* Set the back porch and front porch */
        LCD_WriteReg(LCD_REG_9, 0x0000); /* Set non-display area refresh cycle ISC[3:0] */
        LCD_WriteReg(LCD_REG_10, 0x0000); /* FMARK function */
        LCD_WriteReg(LCD_REG_12, 0x0000); /* RGB interface setting */
        LCD_WriteReg(LCD_REG_13, 0x0000); /* Frame marker Position */
        LCD_WriteReg(LCD_REG_15, 0x0000); /* RGB interface polarity */
        
        /* Power On sequence -----------------------------------------------------*/
        LCD_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
        LCD_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
        LCD_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
        LCD_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude */
        _delay_(20);                      /* Dis-charge capacitor power voltage (200ms) */
        LCD_WriteReg(LCD_REG_16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
        LCD_WriteReg(LCD_REG_17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
        _delay_(5);                       /* Delay 50 ms */
        LCD_WriteReg(LCD_REG_18, 0x0139); /* VREG1OUT voltage */
        _delay_(5);                       /* Delay 50 ms */
        LCD_WriteReg(LCD_REG_19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
        LCD_WriteReg(LCD_REG_41, 0x0013); /* VCM[4:0] for VCOMH */
        _delay_(5);                       /* Delay 50 ms */
        LCD_WriteReg(LCD_REG_32, 0x0000); /* GRAM horizontal Address */
        LCD_WriteReg(LCD_REG_33, 0x0000); /* GRAM Vertical Address */
        
        /* Adjust the Gamma Curve (ILI9325)---------------------------------------*/
        LCD_WriteReg(LCD_REG_48, 0x0007);
        LCD_WriteReg(LCD_REG_49, 0x0302);
        LCD_WriteReg(LCD_REG_50, 0x0105);
        LCD_WriteReg(LCD_REG_53, 0x0206);
        LCD_WriteReg(LCD_REG_54, 0x0808);
        LCD_WriteReg(LCD_REG_55, 0x0206);
        LCD_WriteReg(LCD_REG_56, 0x0504);
        LCD_WriteReg(LCD_REG_57, 0x0007);
        LCD_WriteReg(LCD_REG_60, 0x0105);
        LCD_WriteReg(LCD_REG_61, 0x0808);
        
        /* Set GRAM area ---------------------------------------------------------*/
        LCD_WriteReg(LCD_REG_80, 0x0000); /* Horizontal GRAM Start Address */
        LCD_WriteReg(LCD_REG_81, 0x00EF); /* Horizontal GRAM End Address */
        LCD_WriteReg(LCD_REG_82, 0x0000); /* Vertical GRAM Start Address */
        LCD_WriteReg(LCD_REG_83, 0x013F); /* Vertical GRAM End Address */
        
        LCD_WriteReg(LCD_REG_96,  0xA700); /* Gate Scan Line(GS=1, scan direction is G320~G1) */
        LCD_WriteReg(LCD_REG_97,  0x0001); /* NDL,VLE, REV */
        LCD_WriteReg(LCD_REG_106, 0x0000); /* set scrolling line */
        
        /* Partial Display Control -----------------------------------------------*/
        LCD_WriteReg(LCD_REG_128, 0x0000);
        LCD_WriteReg(LCD_REG_129, 0x0000);
        LCD_WriteReg(LCD_REG_130, 0x0000);
        LCD_WriteReg(LCD_REG_131, 0x0000);
        LCD_WriteReg(LCD_REG_132, 0x0000);
        LCD_WriteReg(LCD_REG_133, 0x0000);
        
        /* Panel Control ---------------------------------------------------------*/
        LCD_WriteReg(LCD_REG_144, 0x0010);
        LCD_WriteReg(LCD_REG_146, 0x0000);
        LCD_WriteReg(LCD_REG_147, 0x0003);
        LCD_WriteReg(LCD_REG_149, 0x0110);
        LCD_WriteReg(LCD_REG_151, 0x0000);
        LCD_WriteReg(LCD_REG_152, 0x0000);
        
        /* set GRAM write direction and BGR = 1 */
        /* I/D=00 (Horizontal : increment, Vertical : decrement) */
        /* AM=1 (address is updated in vertical writing direction) */
        LCD_WriteReg(LCD_REG_3, 0x1008);
        LCD_WriteReg(LCD_REG_7, 0x0133); /* 262K color and display ON */ 
    } 
}


void _delay_(uint32_t ms)
{
    vTaskDelay(ms);
}


