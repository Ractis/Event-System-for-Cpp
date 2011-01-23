/* ------------------------------------------------------------------------- */
/*
 *  Ripple/Kernel/Events/Convinience.h
 *
 *  Copyright (c) 2011, Ractis. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    - Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    - Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *    - No names of its contributors may be used to endorse or promote
 *      products derived from this software without specific prior written
 *      permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* ------------------------------------------------------------------------- */

#ifndef ___RIPPLE_KERNEL_EVENTS_CONVENIENCE_H___
#define ___RIPPLE_KERNEL_EVENTS_CONVENIENCE_H___

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#include <Ripple/Kernel/Events/EventTraits.h>
#include <boost/preprocessor/cat.hpp>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
/**
	@brief Event 関連の型を定義するマクロ
	@note
	 - SPXXXEventDispatcher
	 - XXXEventListener
	 - XXXEventSmartListener
 */
#define RIPPLE_DECL_EVENTTYPES( EVT )																			\
	typedef Ripple::Events::EventTraits< EVT >			BOOST_PP_CAT( EVT, Traits );							\
	typedef BOOST_PP_CAT( EVT, Traits::SPDispatcher )	BOOST_PP_CAT( BOOST_PP_CAT( SP, EVT ), Dispatcher );	\
	typedef BOOST_PP_CAT( EVT, Traits::TListener )		BOOST_PP_CAT( EVT, Listener );							\
	typedef BOOST_PP_CAT( EVT, Traits::TSmartListener )	BOOST_PP_CAT( EVT, SmartListener );

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#endif // ___RIPPLE_KERNEL_EVENTS_CONVENIENCE_H___
