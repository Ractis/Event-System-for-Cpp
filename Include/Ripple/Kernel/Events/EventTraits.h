/* ------------------------------------------------------------------------- */
/*
 *  Ripple/Kernel/Events/EventTraits.h
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

#ifndef ___RIPPLE_KERNEL_EVENTS_EVENTTRAITS_H___
#define ___RIPPLE_KERNEL_EVENTS_EVENTTRAITS_H___

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#include <Ripple/Kernel/Events/Delegate.h>
#include <memory>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
namespace Ripple
{
namespace Kernel
{
namespace Events
{

	// Forward Declaration
	template< typename TEvent >		struct EventTraits;
	template< typename TEvent >		class SmartEventListener;
	template< typename TEvent >		class EventDispatcherImpl;

	/**
		@brief イベントクラスの Traits
		@author	Ractis
	 */
	template < typename TEvent >
	struct EventTraits
	{
		typedef typename TEvent::TNameValue		TNameValue;		///< イベント識別子
		typedef typename TEvent::TNameParam		TNameParam;		///< イベント識別子パラメータ
		typedef Delegate<TEvent&>				TListener;		///< イベントリスナー
		typedef SmartEventListener<TEvent>		TSmartListener;	///< スマートイベントリスナー
		typedef EventDispatcherImpl<TEvent>		TDispatcher;	///< イベントディスパッチャ
		typedef std::shared_ptr<TDispatcher>	SPDispatcher;	///< イベントディスパッチャスマートポインタ
	};

}
}
}

#endif // ___RIPPLE_KERNEL_EVENTS_EVENTTRAITS_H___
