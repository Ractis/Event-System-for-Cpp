/* ------------------------------------------------------------------------- */
/*
 *  Ripple/Kernel/Events/SmartEventListener.h
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

#ifndef ___RIPPLE_KERNEL_EVENTS_SMARTEVENTLISTENER_H___
#define ___RIPPLE_KERNEL_EVENTS_SMARTEVENTLISTENER_H___

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#include <Ripple/Kernel/Events/EventTraits.h>
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>

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
		@brief	自動的に RemoveEventListener を呼び出す EventListener 管理クラス
		@author	Ractis
	 */
	template < typename TEvent >
	class SmartEventListener
		: private boost::noncopyable
	{
	public:
		typedef EventTraits<TEvent>				Traits;
		typedef typename Traits::TNameValue		TNameValue;
		typedef typename Traits::TNameParam		TNameParam;
		typedef typename Traits::TListener		TListener;
		typedef typename Traits::SPDispatcher	SPDispatcher;

	private:
		typedef boost::unordered_multimap< SPDispatcher, TNameValue > TMap;

	private:
		const TListener		m_Listener;	///< イベントリスナー
		TMap				m_Map;		///< 登録マップ

	public:
		SmartEventListener( const TListener& Listener )
			: m_Listener	( Listener )
		{
		}

		/**
			@brief	ひとつのイベントに登録するコンストラクタ
			@param[in]	Listener	登録するイベントリスナー
			@param[in]	pTarget		登録先のイベントディスパッチャ
			@param[in]	Name		登録するイベント名
		 */
		SmartEventListener( const TListener& Listener, const SPDispatcher& pTarget, TNameParam Name )
			: m_Listener	( Listener )
		{
			Add( pTarget, Name );
		}

		/**
			@brief	デストラクタ
		 */
		~SmartEventListener()
		{
			BOOST_FOREACH ( auto& e, m_Map )
			{
				e.first->RemoveEventListener( e.second, m_Listener );
			}
		}

		/**
			@brief	指定のイベントに登録
			@param[in]	pTarget	登録先のイベントディスパッチャ
			@param[in]	Name	登録するイベント名
		 */
		void Add( SPDispatcher pTarget, TNameParam Name )
		{
			pTarget->AddEventListener( Name, m_Listener );

			m_Map.insert( TMap::value_type( pTarget, Name ) );
		}
	};

}
}
}

#endif ___RIPPLE_KERNEL_EVENTS_SMARTEVENTLISTENER_H___
