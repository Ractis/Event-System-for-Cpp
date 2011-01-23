/* ------------------------------------------------------------------------- */
/*
 *  Ripple/Kernel/Events/Event.h
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

#ifndef ___RIPPLE_KERNEL_EVENTS_EVENT_H___
#define ___RIPPLE_KERNEL_EVENTS_EVENT_H___

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/call_traits.hpp>

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
		@brief	イベントクラス
		@author	Ractis
		@tparam	TName	イベント識別子の型
	 */
	template < typename TName >
	class BasicEvent
		: private boost::noncopyable
	{
	private:
		typedef boost::call_traits<TName>	TNameTraits;

	public:
		typedef	typename TNameTraits::value_type	TNameValue;		///< イベント識別子の型
		typedef typename TNameTraits::param_type	TNameParam;		///< イベント識別子パラメータの型

	private:
		/**
			@brief	イベント識別子
			@note
			Event は、基本的に保持される事が無い（送出時に作成→破棄される）ため、参照型として識別子を持っています。
		 */
		TNameParam	m_Name;

	public:
		/**
			@brief	コンストラクタ
			@param[in]	Name	イベント識別子
		 */
		BasicEvent( TNameParam Name )
			: m_Name	( Name )
		{
		}

		inline TNameParam Name() const { return m_Name; }
	};

	typedef BasicEvent< std::string >	Event;

}
}
}

#endif // ___RIPPLE_KERNEL_EVENTS_EVENT_H___
