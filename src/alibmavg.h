////////////////////////////////////////////////////////////////////////////////
/**
 * @file        alibmavg.h
 * 
 * @author      Martin Legleiter
 * 
 * @brief       TODO
 * 
 * @copyright   (c) 2022 Martin Legleiter
 * 
 * @license     Use of this source code is governed by an MIT-style
 *              license that can be found in the LICENSE file or at
 *              @see https://opensource.org/licenses/MIT.
 */
////////////////////////////////////////////////////////////////////////////////

#ifndef __ALIBMAVG_H__
#define __ALIBMAVG_H__

/*-----------------------------------------------------------*/

#include <stddef.h>
#include <math.h>

/*-----------------------------------------------------------*/

/*
 * Simple Moving Average
 */
#define SMA_FUNCTION( type_t, xName, SIZE )     \
                                                \
    type_t xName( type_t xValue )               \
    {                                           \
        static type_t pxVal[ SIZE ];            \
        static type_t xSum = 0;                 \
        static size_t xNbrOfVals = 0;           \
        static size_t xValIdx = 0;              \
                                                \
        if( xNbrOfVals < SIZE )                 \
        {                                       \
            pxVal[ xNbrOfVals ] = xValue;       \
            xSum += pxVal[ xNbrOfVals++ ];      \
        }                                       \
        else                                    \
        {                                       \
            xSum -= pxVal[ xValIdx ];           \
            pxVal[ xValIdx ] = xValue ;         \
            xSum += pxVal[ xValIdx++ ];         \
                                                \
            if( xValIdx == SIZE )               \
            {                                   \
                xValIdx = 0;                    \
            }                                   \
        }                                       \
                                                \
        return xSum / ( type_t ) xNbrOfVals;    \
    }

/*-----------------------------------------------------------*/

/*
 * Weighted Moving Average
 */
#define WMA_FUNCTION( type_t, xName, SIZE )         \
                                                    \
    type_t xName( type_t xValue )                   \
    {                                               \
        static type_t pxVal[ SIZE ];                \
        double dSum = 0;                            \
        static size_t xNbrOfVals = 0;               \
        size_t xPoints = 1;                         \
                                                    \
        if( xNbrOfVals == 0 )                       \
        {                                           \
            pxVal[ xNbrOfVals++ ] = xValue;         \
        }                                           \
        else if( xNbrOfVals < SIZE )                \
        {                                           \
            pxVal[ xNbrOfVals++ ] = xValue;         \
            xPoints = ( xNbrOfVals * ( xNbrOfVals + 1 ) ) / 2;  \
        }                                           \
        else                                        \
        {                                           \
            for( size_t i = 0; i < SIZE - 1; i++ )  \
            {                                       \
                pxVal[ i ] = pxVal[ i + 1 ];        \
            }                                       \
                                                    \
            pxVal[ SIZE - 1 ] = xValue;             \
            xPoints = ( SIZE * ( SIZE + 1 ) ) / 2;  \
        }                                           \
                                                    \
        for( size_t i = 0; i < xNbrOfVals; i++ )    \
        {                                           \
            dSum += ( ( double ) pxVal[ i ] * ( ( double ) ( i + 1 ) / ( double ) xPoints ) );  \
        }                                           \
                                                    \
        return ( type_t ) lround( dSum );           \
    }

/*-----------------------------------------------------------*/

/*
 * TODO: This is a dummy for the Exponential Moving Average.
 */
#define EMA_FUNCTION( type_t, xName, SIZE ) \
                                            \
    type_t xName( type_t xValue )           \
    {                                       \
        return xValue;                      \
    }

/*-----------------------------------------------------------*/

#endif /* __ALIBMAVG_H__ */
