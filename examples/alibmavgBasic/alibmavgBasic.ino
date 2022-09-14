////////////////////////////////////////////////////////////////////////////////
/**
 * @file        alibmavgBasic.ino
 *
 * @author      Martin Legleiter
 *
 * @brief       TODO
 * 
 * @copyright   2022 Martin Legleiter
 * 
 * @license     Use of this source code is governed by an MIT-style
 *              license that can be found in the LICENSE file or at
 *              @see https://opensource.org/licenses/MIT.
 */
////////////////////////////////////////////////////////////////////////////////

#include <alibmavg.h>

/*-----------------------------------------------------------*/

SMA_FUNCTION( long, SMAFunction1,  8 );
SMA_FUNCTION( long, SMAFunction2, 64 );
SMA_FUNCTION( long, WMAFunction1,  8 );
SMA_FUNCTION( long, WMAFunction2, 64 );

/*-----------------------------------------------------------*/

void setup( void )
{
    Serial.begin( 9600 );
}
/*-----------------------------------------------------------*/

void loop( void )
{
    long randomValue = random( -100, 101 );

    Serial.print( randomValue );
    Serial.print( ',' );
    Serial.print( SMAFunction1( randomValue ) );
    Serial.print( ',' );
    Serial.print( SMAFunction2( randomValue ) );
    Serial.print( ',' );
    Serial.print( WMAFunction1( randomValue ) );
    Serial.print( ',' );
    Serial.println( WMAFunction2( randomValue ) );

    delay( 20 );
}
