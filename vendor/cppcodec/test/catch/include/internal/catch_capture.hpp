/*
 *  Created by Phil on 18/10/2010.
 *  Copyright 2010 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_CAPTURE_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_CAPTURE_HPP_INCLUDED

#include "catch_assertionhandler.h"
#include "catch_message.h"
#include "catch_interfaces_capture.h"

#if !defined(CATCH_CONFIG_DISABLE)

#if !defined(CATCH_CONFIG_DISABLE_STRINGIFICATION)
  #define CATCH_INTERNAL_STRINGIFY(...) #__VA_ARGS__
#else
  #define CATCH_INTERNAL_STRINGIFY(...) "Disabled by CATCH_CONFIG_DISABLE_STRINGIFICATION"
#endif

#if defined(CATCH_CONFIG_FAST_COMPILE)

///////////////////////////////////////////////////////////////////////////////
// Another way to speed-up compilation is to omit local try-catch for REQUIRE*
// macros.
#define INTERNAL_CATCH_TRY
#define INTERNAL_CATCH_CATCH( capturer )

#else // CATCH_CONFIG_FAST_COMPILE

#define INTERNAL_CATCH_TRY try
#define INTERNAL_CATCH_CATCH( handler ) catch(...) { handler.handleUnexpectedInflightException(); }

#endif

#define INTERNAL_CATCH_REACT( handler ) handler.complete();

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_TEST( macroName, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition ); \
        INTERNAL_CATCH_TRY { \
            CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS \
            catchAssertionHandler.handleExpr( Catch::Decomposer() <= __VA_ARGS__ ); \
            CATCH_INTERNAL_UNSUPPRESS_PARENTHESES_WARNINGS \
        } INTERNAL_CATCH_CATCH( catchAssertionHandler ) \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( (void)0, false && static_cast<bool>( !!(__VA_ARGS__) ) ) // the expression here is never evaluated at runtime but it forces the compiler to give it a look
    // The double negation silences MSVC's C4800 warning, the static_cast forces short-circuit evaluation if the type has overloaded &&.

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_IF( macroName, resultDisposition, ... ) \
    INTERNAL_CATCH_TEST( macroName, resultDisposition, __VA_ARGS__ ); \
    if( Catch::getResultCapture().lastAssertionPassed() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_ELSE( macroName, resultDisposition, ... ) \
    INTERNAL_CATCH_TEST( macroName, resultDisposition, __VA_ARGS__ ); \
    if( !Catch::getResultCapture().lastAssertionPassed() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_NO_THROW( macroName, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition ); \
        try { \
            static_cast<void>(__VA_ARGS__); \
            catchAssertionHandler.handleExceptionNotThrownAsExpected(); \
        } \
        catch( ... ) { \
            catchAssertionHandler.handleUnexpectedInflightException(); \
        } \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS( macroName, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast<void>(__VA_ARGS__); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( ... ) { \
                catchAssertionHandler.handleExceptionThrownAsExpected(); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_AS( macroName, exceptionType, resultDisposition, expr ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(expr) ", " CATCH_INTERNAL_STRINGIFY(exceptionType), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast<void>(expr); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( exceptionType const& ) { \
                catchAssertionHandler.handleExceptionThrownAsExpected(); \
            } \
            catch( ... ) { \
                catchAssertionHandler.handleUnexpectedInflightException(); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )


///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_MSG( macroName, messageType, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, Catch::StringRef(), resultDisposition ); \
        catchAssertionHandler.handleMessage( messageType, ( Catch::MessageStream() << __VA_ARGS__ + ::Catch::StreamEndStop() ).m_stream.str() ); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_INFO( macroName, log ) \
    Catch::ScopedMessage INTERNAL_CATCH_UNIQUE_NAME( scopedMessage )( Catch::MessageBuilder( macroName, CATCH_INTERNAL_LINEINFO, Catch::ResultWas::Info ) << log );

///////////////////////////////////////////////////////////////////////////////
// Although this is matcher-based, it can be used with just a string
#define INTERNAL_CATCH_THROWS_STR_MATCHES( macroName, resultDisposition, matcher, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__) ", " CATCH_INTERNAL_STRINGIFY(matcher), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast<void>(__VA_ARGS__); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( ... ) { \
                Catch::handleExceptionMatchExpr( catchAssertionHandler, matcher, #matcher ); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

#endif // CATCH_CONFIG_DISABLE

#endif // TWOBLUECUBES_CATCH_CAPTURE_HPP_INCLUDED
