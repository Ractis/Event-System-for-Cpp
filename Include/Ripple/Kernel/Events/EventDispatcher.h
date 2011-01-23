/* ------------------------------------------------------------------------- */
/*
 *  Ripple/Kernel/Events/EventDispatcher.h
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

#ifndef ___RIPPLE_KERNEL_EVENTS_EVENTDISPATCHER_H___
#define ___RIPPLE_KERNEL_EVENTS_EVENTDISPATCHER_H___

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#include <Ripple/Kernel/Events/EventDispatcherImpl.h>
#include <boost/noncopyable.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
namespace Ripple
{
namespace Kernel
{
namespace Events
{

/**
	@brief	イベントディスパッチャのイベント型最大数
 */
#define RIPPLE_PP_EVENT_DISPATCHER_MAX_ARITY		10


	/// NullType
	struct NullType { };

#define RIPPLE_PP_EVENT_NULLTYPE( z, n, unused )	NullType

/**
	@brief	EventDispatcher テンプレート特殊化プリプロセッサ
	@code
		< TEvt0, NullType, NullType, NullType, ... >

		< TEvt0, TEvt1, NullType, NullType, ... >
	@endcode
 */
#define RIPPLE_PP_EVENT_DISPATCHER_SPECIALIZATION( count )																					\
	BOOST_PP_ENUM_PARAMS( count, TEvt )																										\
	BOOST_PP_ENUM_TRAILING( BOOST_PP_SUB( BOOST_PP_INC( RIPPLE_PP_EVENT_DISPATCHER_MAX_ARITY ), count ), RIPPLE_PP_EVENT_NULLTYPE, ~ )

/**
	@brief	EventDispatcher typedef プリプロセッサ
 */
#define RIPPLE_PP_EVENT_DISPATCHER_TYPEDEFS( z, n, unused )														\
	typedef typename EventTraits< BOOST_PP_CAT( TEvt, n ) >					BOOST_PP_CAT( EventTraits, n );		\
	typedef typename EventTraits< BOOST_PP_CAT( TEvt, n ) >::TDispatcher	BOOST_PP_CAT( TDispatcher, n );		\
	typedef typename EventTraits< BOOST_PP_CAT( TEvt, n ) >::SPDispatcher	BOOST_PP_CAT( SPDispatcher, n );	\
	typedef typename EventTraits< BOOST_PP_CAT( TEvt, n ) >::TNameParam		BOOST_PP_CAT( TEventNameParam, n );	\
	typedef typename EventTraits< BOOST_PP_CAT( TEvt, n ) >::TListener		BOOST_PP_CAT( TListener, n );

/**
	@brief	EventDispatcher メソッドプリプロセッサ
 */
#define RIPPLE_PP_EVENT_DISPATCHER_METHODS( z, n, unused )								\
	inline void AddEventListener( BOOST_PP_CAT( TEventNameParam, n ) Name,				\
								  const BOOST_PP_CAT( TListener, n ) & Listener )		\
	{																					\
		BOOST_PP_CAT( m_pImpl, n )->AddEventListener( Name, Listener );					\
	}																					\
	inline void RemoveEventListener( BOOST_PP_CAT( TEventNameParam, n ) Name,			\
									 const BOOST_PP_CAT( TListener, n ) & Listener )	\
	{																					\
		BOOST_PP_CAT( m_pImpl, n )->RemoveEventListener( Name, Listener );				\
	}																					\
	inline bool DispatchEvent( BOOST_PP_CAT( TEvt, n ) & Evt )							\
	{																					\
		return BOOST_PP_CAT( m_pImpl, n )->DispatchEvent( Evt );							\
	}																					\
	inline operator BOOST_PP_CAT( SPDispatcher, n ) ()									\
	{																					\
		return BOOST_PP_CAT( m_pImpl, n );												\
	}

/**
	@brief	EventDispatcher	メンバプリプロセッサ
 */
#define RIPPLE_PP_EVENT_DISPATCHER_MEMBER( z, n, unused )		\
	BOOST_PP_CAT( SPDispatcher, n ) BOOST_PP_CAT( m_pImpl, n );

/**
	@brief	EventDispatcher コンストラクタパラメータプリプロセッサ
 */
#define RIPPLE_PP_EVENT_DOSPATCHER_CONSTRUCT_PARAM( z, n, unused )	\
	BOOST_PP_CAT( m_pImpl, n )	( std::make_shared< BOOST_PP_CAT( TDispatcher, n ) >() )

/**
	@brief	EvenrDispatcher クラスプリプロセッサ
 */
#define RIPPLE_PP_EVENT_DISPATCHER_CLASS( count )										\
	template < BOOST_PP_ENUM_PARAMS( count, class TEvt ) >								\
	class EventDispatcher< RIPPLE_PP_EVENT_DISPATCHER_SPECIALIZATION( count ) >			\
		: boost::noncopyable															\
	{																					\
	public:																				\
		BOOST_PP_REPEAT( count, RIPPLE_PP_EVENT_DISPATCHER_TYPEDEFS, ~ )				\
		BOOST_PP_REPEAT( count, RIPPLE_PP_EVENT_DISPATCHER_METHODS, ~ )					\
	private:																			\
		BOOST_PP_REPEAT( count, RIPPLE_PP_EVENT_DISPATCHER_MEMBER, ~ )					\
	public:																				\
		EventDispatcher()																\
			: BOOST_PP_ENUM( count, RIPPLE_PP_EVENT_DOSPATCHER_CONSTRUCT_PARAM, ~ ) { }	\
	};

/**
	@brief	EventDispatcher 定義プリプロセッサ
 */
#define RIPPLE_PP_EVENT_DISPATCHER_DECL( z, n, unused ) \
	RIPPLE_PP_EVENT_DISPATCHER_CLASS( BOOST_PP_INC( n ) )

/**
	@brief	EventDispatcher	イベント型定義プリプロセッサ
 */
#define RIPPLE_PP_EVENT_DISPATCHER_EVENTS( z, n, unused ) \
	class BOOST_PP_CAT( TEvt, n ) = NullType


// Forward Declaration
template < class TEvt0, BOOST_PP_ENUM_SHIFTED( RIPPLE_PP_EVENT_DISPATCHER_MAX_ARITY, RIPPLE_PP_EVENT_DISPATCHER_EVENTS, ~ ), class Ignore = NullType >
class EventDispatcher;

// Declaration
BOOST_PP_REPEAT( RIPPLE_PP_EVENT_DISPATCHER_MAX_ARITY, RIPPLE_PP_EVENT_DISPATCHER_DECL, ~ )

}
}
}

#endif // ___RIPPLE_KERNEL_EVENTS_EVENTDISPATCHER_H___
