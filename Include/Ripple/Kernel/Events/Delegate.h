/* ------------------------------------------------------------------------- */
/*
 *  Ripple/Kernel/Events/Delegate.h
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

#ifndef ___RIPPLE_KERNEL_EVENTS_DELEGATE_H___
#define ___RIPPLE_KERNEL_EVENTS_DELEGATE_H___

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>

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
		@brief	unordered_set/map 等のハッシュコンテナで管理できるデリゲート
		@author	Ractis
	 */
	template < typename Arg >
	class Delegate
	{
	private:
		class HolderAbstract
			: private boost::noncopyable
		{
		public:
			void*	pObj;
			void*	pMethod;

		public:
			HolderAbstract( void* pObj, void* pMethod )
				: pObj		( pObj )
				, pMethod	( pMethod )
			{
			}

			virtual void Call( Arg ) const = 0;
		};

		/**
			@brief	特定のクラスメソッドをバインドするホルダー
		 */
		template < typename TClass >
		class HolderDynamic
			: public HolderAbstract
		{
		protected:
			typedef void (TClass::*TMethodPtr)( Arg );

		protected:
			/// void* から MethodPtr へ変換
			inline TMethodPtr const MethodPtr() const { return *reinterpret_cast<TMethodPtr const*>( &pMethod ); }

		public:
			HolderDynamic( TClass* pClass, TMethodPtr pMethod )
				: HolderAbstract	( pClass, *reinterpret_cast<void**>( &pMethod ) )
			{
			}

			virtual void Call( Arg arg ) const
			{
				( reinterpret_cast<TClass* const>( pObj )->*MethodPtr() )( arg );
			}
		};

	private:
		typedef std::shared_ptr<HolderAbstract>	SPHolder;

	private:
		SPHolder	m_pHolder;

	public:
		/// コピーコンストラクタ
		Delegate( const Delegate& rhs )
			: m_pHolder	( rhs.m_pHolder )
		{
		}

		template < typename TClass >
		Delegate( TClass* pClass, void (TClass::*pMethod)( Arg ) )
			: m_pHolder	( std::make_shared<HolderDynamic<TClass>>( pClass, pMethod ) )
		{
		}

	public:
		inline void Reset()
		{
			m_pHolder.reset();
		}

		inline bool operator ! () const
		{
			return !m_pHolder;
		}

		inline void operator () ( Arg arg ) const
		{
			m_pHolder->Call( arg );
		}

		inline Delegate& operator = ( const Delegate& rhs )
		{
			m_pHolder = rhs.m_pHolder;

			return *this;
		}

	public:		// Functor
		struct Hash
			: public std::unary_function< Delegate, size_t >
		{
			size_t operator () ( const Delegate& rhs ) const
			{
				size_t seed = 0;
				{
					using namespace boost;
					hash_combine( seed, rhs.m_pHolder->pObj );
					hash_combine( seed, rhs.m_pHolder->pMethod );
				}
				return seed;
			}
		};

		struct EqualTo
			: public std::binary_function< Delegate, Delegate, bool >
		{
			bool operator () ( const Delegate& lhs, const Delegate& rhs ) const
			{
				if ( !lhs )	return !rhs;

				return lhs.m_pHolder->pObj		== rhs.m_pHolder->pObj
					&& lhs.m_pHolder->pMethod	== rhs.m_pHolder->pMethod;
			}
		};
	};

}
}
}

#endif // ___RIPPLE_KERNEL_EVENTS_DELEGATE_H___
