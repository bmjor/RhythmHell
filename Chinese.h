/*!
 * @defgroup ST7735
 * @brief ST7735 LCD
 <table>
<caption id="ChineseAdafruitLCDpins">Adafruit ST7735R pins </caption>
<tr><th>Pin <th>Connection <th>Description
<tr><td>10<td>+3.3<td>Backlight
<tr><td>9 <td>nc  <td>SPI1 MISO (used for SDC)
<tr><td>8 <td>PB9 <td>SPI1 SCLK clock out
<tr><td>7 <td>PB8 <td>SPI1 PICO data out
<tr><td>6 <td>PB6 <td>SPI1 CS0=TFT_CS
<tr><td>5 <td>nc  <td>CARD_CS (used for SDC)
<tr><td>4 <td>PA13<td>Data/Command(GPIO), high for data, low for command
<tr><td>3 <td>PB15<td>RESET, low to reset,  (GPIO)
<tr><td>2 <td>+3.3<td>VCC
<tr><td>1 <td>Gnd <td>ground
</table>

 <table>
<caption id="Chinesewidehkpins">wide.hk ST7735R with ADXL345 accelerometer pins </caption>
<tr><th>Pin<th>Connection
<tr><td>VCC  <td> +3.3 V
<tr><td>GND  <td> Ground
<tr><td>!SCL <td> SPI1 SCLK: PB9 clock
<tr><td>!SDA <td> SPI1 PICO: PB8 MOSI SPI data from microcontroller to TFT or SDC
<tr><td>DC   <td> GPIO       PA13 TFT data/command
<tr><td>RES  <td> GPIO       PB15 TFT reset
<tr><td>CS   <td> SPI1 CS0:  PB6 TFT_CS, active low to enable TFT
<tr><td>*CS  <td> (NC) SDC_CS, active low to enable SDC
<tr><td>MISO <td> (NC) MISO SPI data from SDC to microcontroller
<tr><td>SDA  <td> (NC) I2C data for ADXL345 accelerometer
<tr><td>SCL  <td> (NC) I2C clock for ADXL345 accelerometer
<tr><td>SDO  <td> (NC) I2C alternate address for ADXL345 accelerometer
<tr><td>Backlight + - Light, backlight connected to +3.3 V
</table>


<table>
<caption id="Chinesewidehkpins335">wide.hk ST7735R with ADXL335 accelerometer pins </caption>
<tr><th>Pin<th>Connection
<tr><td>VCC  <td> +3.3 V
<tr><td>GND  <td> Ground
/<tr><td>!SCL<td> SPI1 SCLK: PB9
<tr><td>!SDA <td> SPI1 PICO: PB8 MOSI SPI data from microcontroller to TFT or SDC
<tr><td>DC   <td> GPIO       PA13 TFT data/command
<tr><td>RES  <td> GPIO       PB15 TFT reset
<tr><td>CS   <td> SPI1 CS0:  PB6 TFT_CS, active low to enable TFT
<tr><td>*CS  <td> (NC) SDC_CS, active low to enable SDC
<tr><td>MISO <td> (NC) MISO SPI data from SDC to microcontroller
<tr><td>X<td> (NC) analog input X-axis from ADXL335 accelerometer
<tr><td>Y<td> (NC) analog input Y-axis from ADXL335 accelerometer
<tr><td>Z<td> (NC) analog input Z-axis from ADXL335 accelerometer
<tr><td>Backlight + <td> Light, backlight connected to +3.3 V
</table>

<table>
<caption id="ChineseHiLetgopins">HiLetgo ST7735 TFT and SDC pins </caption>
<tr><th>signal<th>Pin<th>Connection
<tr><td>LED-   <td>16<td>TFT, to ground
<tr><td>LED+   <td>15<td>TFT, to +3.3 V
<tr><td>SD_CS  <td>14<td>SDC, to chip select
<tr><td>MOSI   <td>13<td>SDC, to MOSI
<tr><td>MISO   <td>12<td>SDC, to MISO
<tr><td>SCK    <td>11<td>SDC, to serial clock
<tr><td>CS     <td>10<td>TFT, to PB6  SPI1 CS0
<tr><td>SCL    <td> 9<td>TFT, to PB9  SPI1 SCLK
<tr><td>SDA    <td> 8<td>TFT, to PB8  MOSI SPI1 PICO
<tr><td>A0     <td> 7<td>TFT, to PA13 Data/Command, high for data, low for command
<tr><td>RESET  <td> 6<td>TFT, to PB15 reset (GPIO), low to reset
<tr><td>NC     <td>3,4,5<td>not connected
<tr><td>VCC    <td> 2<td>to +3.3 V
<tr><td>GND    <td> 1<td>to ground
</table>

<table>
<caption id="ChineseTyenazapins">Tyenaza Tyenazaqhf72mi9s3 pins </caption>
<tr><th>signal<th>Pin<th>Connection
<tr><td>LED <td>8<td> to +3.3 V
<tr><td>SCK <td>7<td>SCLK         to PB9 SPI1 SCLK
<tr><td>SDA <td>6<td>MOSI,        to PB8 SPI1 PICO
<tr><td>A0  <td>5<td>Data/Command to PA13 (GPIO), high for data, low for command
<tr><td>RESET <td>4<td>to PB15 (GPIO), low to reset
<tr><td>CS  <td>3<td>to PB6 SPI1 CS0:
<tr><td>Gnd <td>2<td>to ground
<tr><td>VCC <td>1<td>to +3.3 V
</table>
 * @{*/
/**
 * @file      Chinese.h
 * @brief     Chinese output to LCD
 * @details   Chinese character/string output to ST7735R display<br>
 * @version   ECE319K v1.0
 * @author    Amina Meddad and Jonathan Valvano
 * @copyright Copyright 2024 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      August 14, 2024
  <table>
<caption id="ChineseAdafruitLCDpins2">Adafruit ST7735R pins </caption>
<tr><th>Pin <th>Connection <th>Description
<tr><td>10<td>+3.3<td>Backlight
<tr><td>9 <td>nc  <td>SPI1 MISO (used for SDC)
<tr><td>8 <td>PB9 <td>SPI1 SCLK clock out
<tr><td>7 <td>PB8 <td>SPI1 PICO data out
<tr><td>6 <td>PB6 <td>SPI1 CS0=TFT_CS
<tr><td>5 <td>nc  <td>CARD_CS (used for SDC)
<tr><td>4 <td>PA13<td>Data/Command(GPIO), high for data, low for command
<tr><td>3 <td>PB15<td>RESET, low to reset,  (GPIO)
<tr><td>2 <td>+3.3<td>VCC
<tr><td>1 <td>Gnd <td>ground
</table>

 <table>
<caption id="Chinesewidehkpins2">wide.hk ST7735R with ADXL345 accelerometer pins </caption>
<tr><th>Pin<th>Connection
<tr><td>VCC  <td> +3.3 V
<tr><td>GND  <td> Ground
<tr><td>!SCL <td> SPI1 SCLK: PB9 clock
<tr><td>!SDA <td> SPI1 PICO: PB8 MOSI SPI data from microcontroller to TFT or SDC
<tr><td>DC   <td> GPIO       PA13 TFT data/command
<tr><td>RES  <td> GPIO       PB15 TFT reset
<tr><td>CS   <td> SPI1 CS0:  PB6 TFT_CS, active low to enable TFT
<tr><td>*CS  <td> (NC) SDC_CS, active low to enable SDC
<tr><td>MISO <td> (NC) MISO SPI data from SDC to microcontroller
<tr><td>SDA  <td> (NC) I2C data for ADXL345 accelerometer
<tr><td>SCL  <td> (NC) I2C clock for ADXL345 accelerometer
<tr><td>SDO  <td> (NC) I2C alternate address for ADXL345 accelerometer
<tr><td>Backlight + - Light, backlight connected to +3.3 V
</table>


<table>
<caption id="Chinesewidehkpins3352">wide.hk ST7735R with ADXL335 accelerometer pins </caption>
<tr><th>Pin<th>Connection
<tr><td>VCC  <td> +3.3 V
<tr><td>GND  <td> Ground
/<tr><td>!SCL<td> SPI1 SCLK: PB9
<tr><td>!SDA <td> SPI1 PICO: PB8 MOSI SPI data from microcontroller to TFT or SDC
<tr><td>DC   <td> GPIO       PA13 TFT data/command
<tr><td>RES  <td> GPIO       PB15 TFT reset
<tr><td>CS   <td> SPI1 CS0:  PB6 TFT_CS, active low to enable TFT
<tr><td>*CS  <td> (NC) SDC_CS, active low to enable SDC
<tr><td>MISO <td> (NC) MISO SPI data from SDC to microcontroller
<tr><td>X<td> (NC) analog input X-axis from ADXL335 accelerometer
<tr><td>Y<td> (NC) analog input Y-axis from ADXL335 accelerometer
<tr><td>Z<td> (NC) analog input Z-axis from ADXL335 accelerometer
<tr><td>Backlight + <td> Light, backlight connected to +3.3 V
</table>

<table>
<caption id="ChineseHiLetgopins2">HiLetgo ST7735 TFT and SDC pins </caption>
<tr><th>signal<th>Pin<th>Connection
<tr><td>LED-   <td>16<td>TFT, to ground
<tr><td>LED+   <td>15<td>TFT, to +3.3 V
<tr><td>SD_CS  <td>14<td>SDC, to chip select
<tr><td>MOSI   <td>13<td>SDC, to MOSI
<tr><td>MISO   <td>12<td>SDC, to MISO
<tr><td>SCK    <td>11<td>SDC, to serial clock
<tr><td>CS     <td>10<td>TFT, to PB6  SPI1 CS0
<tr><td>SCL    <td> 9<td>TFT, to PB9  SPI1 SCLK
<tr><td>SDA    <td> 8<td>TFT, to PB8  MOSI SPI1 PICO
<tr><td>A0     <td> 7<td>TFT, to PA13 Data/Command, high for data, low for command
<tr><td>RESET  <td> 6<td>TFT, to PB15 reset (GPIO), low to reset
<tr><td>NC     <td>3,4,5<td>not connected
<tr><td>VCC    <td> 2<td>to +3.3 V
<tr><td>GND    <td> 1<td>to ground
</table>

<table>
<caption id="ChineseTyenazapins2">Tyenaza Tyenazaqhf72mi9s3 pins </caption>
<tr><th>signal<th>Pin<th>Connection
<tr><td>LED <td>8<td> to +3.3 V
<tr><td>SCK <td>7<td>SCLK         to PB9 SPI1 SCLK
<tr><td>SDA <td>6<td>MOSI,        to PB8 SPI1 PICO
<tr><td>A0  <td>5<td>Data/Command to PA13 (GPIO), high for data, low for command
<tr><td>RESET <td>4<td>to PB15 (GPIO), low to reset
<tr><td>CS  <td>3<td>to PB6 SPI1 CS0:
<tr><td>Gnd <td>2<td>to ground
<tr><td>VCC <td>1<td>to +3.3 V
</table>
<br>

  ******************************************************************************/

#ifndef _CHINESE_
#define _CHINESE_
#include <stdint.h>
/**
 * \brief Chinese character set
 */
typedef enum {null, ying1, zhong, wen, kai, shi1, zan, ting, hui, fu, dan, shuan, ren, mo, shi2, ni, ying2, shu, le, wan, jia, yi, er, slash, ex, period, comma,yao, yong, guan, he, tui, chu, dao, cai, huo, zhe,jin,ru,lun,hui1} Chinese_t;



/**
 * Move the cursor to the desired X- and Y-position.  The
 * next character will be printed here.  X=0 is the leftmost
 * column.  Y=0 is the top row. *
 * @param none
 * @param newX  new X-position of the cursor (0<=newX<=7)
 * @param newY  new Y-position of the cursor (0<=newY<=9)
 * @return none
 * @brief  Move Chinese cursor
 */
void Chinese_SetCursor(uint32_t newX, uint32_t newY);

/**
 * Output one Chinese character to the LCD
 * Position determined by Chinese_SetCursor command
 * Color set by ST7735_SetTextColor
 * @param ch 8-bit Chinese character
 * @return none
 * @brief  Output an Chinese character
 */
void Chinese_OutChar(Chinese_t ch);

/**
 * Output an Chinese string to the LCD
 * Position determined by Chinese_SetCursor command
 * Color set by ST7735_SetTextColor.
 * The string will automatically wrap.
 * @param ptr  pointer to null-terminated Chinese string
 * @return none
 * @brief  Output an Chinese string
 */
void Chinese_OutString(Chinese_t *ptr);
#endif
/** @}*/

