////////////////////////////////////////////////////////////////////////////////
/**
 * @file        alibmavg.h
 * 
 * @author      Martin Legleiter
 * 
 * @brief       TODO
 * 
 * @copyright   (c) 2023 Martin Legleiter
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
        static type_t pxBuffer[ SIZE ];         \
        static type_t xSum = 0;                 \
        static size_t xNbrOfVals = 0;           \
        static size_t xBufIdx = 0;              \
                                                \
        if( xNbrOfVals < SIZE )                 \
        {                                       \
            /* For the first SIZE-number of values, we place the given value in     \
            the buffer, add it to the sum, and increment the value counter. */      \
            pxBuffer[ xNbrOfVals ] = xValue;    \
            xSum += pxBuffer[ xNbrOfVals++ ];   \
        }                                       \
        else                                    \
        {                                       \
            /* Substract the least recent value from the sum. */                    \
            xSum -= pxBuffer[ xBufIdx ];        \
                                                \
            /* Place the given value as the most recent one in the buffer. */       \
            pxBuffer[ xBufIdx ] = xValue ;      \
                                                \
            /* Add the most recent value to the sum and increment the index. */     \
            xSum += pxBuffer[ xBufIdx++ ];      \
                                                \
            /* Check if we finished one cycle through the complete buffer, and      \
            reset the index in case. */                                             \
            if( xBufIdx == SIZE )               \
            {                                   \
                xBufIdx = 0;                    \
            }                                   \
        }                                       \
                                                \
        /* Return the average value by dividing the sum by the number of values     \
        in the array. This is particularly important when the array is not          \
        completely filled yet. */                                                   \
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
        static type_t pxBuffer[ SIZE ];             \
        double dSum = 0;                            \
        static size_t xNbrOfVals = 0;               \
        size_t xPoints = 1;                         \
                                                    \
        if( xNbrOfVals == 0 )                       \
        {                                           \
            pxBuffer[ xNbrOfVals++ ] = xValue;      \
        }                                           \
        else if( xNbrOfVals < SIZE )                \
        {                                           \
            pxBuffer[ xNbrOfVals++ ] = xValue;      \
            xPoints = ( xNbrOfVals * ( xNbrOfVals + 1 ) ) / 2; \
        }                                           \
        else                                        \
        {                                           \
            for( size_t i = 0; i < SIZE - 1; i++ )  \
            {                                       \
                pxBuffer[ i ] = pxBuffer[ i + 1 ];  \
            }                                       \
                                                    \
            pxBuffer[ SIZE - 1 ] = xValue;          \
            xPoints = ( SIZE * ( SIZE + 1 ) ) / 2;  \
        }                                           \
                                                    \
        for( size_t i = 0; i < xNbrOfVals; i++ )    \
        {                                           \
            dSum += ( ( double ) pxBuffer[ i ] * ( ( double ) ( i + 1 ) / ( double ) xPoints ) ); \
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
