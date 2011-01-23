/* ------------------------------------------------------------------------- */
/*
 *  Ripple/Kernel/Utils/MapUtils.h
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

#ifndef ___RIPPLE_KERNEL_UTILS_MAPUTILS_H___
#define ___RIPPLE_KERNEL_UTILS_MAPUTILS_H___

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
namespace Ripple
{
namespace Kernel
{
namespace Utils
{

	/**
		@brief	Map/Set 等のコンテナ用ユーティリティ
		@author	Ractis
	 */
	class MapUtils
	{
	private:
		MapUtils();

	public:
		/**
			@brief	指定のキーを持つ要素を探し、コールバック関数を実行
			@param[in]	Cont		コンテナ
			@param[in]	Key			キー
			@param[in]	Callback	コールバック関数 [ void Callback( map::iterator& It, map& Map ) ]
			@retval	true	要素が見つかった
			@retval	false	要素が見つからなかった
		 */
		template < typename TContainer, typename TCallbackFunc >
		inline static bool Find( TContainer& Cont,
								 const typename TContainer::key_type& Key,
								 TCallbackFunc Callback )
		{
			auto it = Cont.find( Key );
			if ( it == Cont.end() ) return false;

			// コールバック関数を実行
			Callback( it, Cont );
			return true;
		}

		/**
			@brief	指定のキーを持つ要素を探し、削除を実行
			@param[in]	Cont	コンテナ
			@param[in]	Key		キー
			@retval true	要素が見つかり、削除が行われた
			@retval false	削除が行われなかった
		 */
		template < typename TContainer >
		inline static bool Erase( TContainer& Cont, const typename TContainer::key_type& Key )
		{
			return Find( Cont, Key, []( typename TContainer::iterator& It, TContainer& Cont )
			{
				Cont.erase( It );
			} );
		}
	};

}
}
}

#endif // ___RIPPLE_KERNEL_UTILS_MAPUTILS_H___
