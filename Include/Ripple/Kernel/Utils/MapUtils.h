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
		@brief	Map/Set ���̃R���e�i�p���[�e�B���e�B
		@author	Ractis
	 */
	class MapUtils
	{
	private:
		MapUtils();

	public:
		/**
			@brief	�w��̃L�[�����v�f��T���A�R�[���o�b�N�֐������s
			@param[in]	Cont		�R���e�i
			@param[in]	Key			�L�[
			@param[in]	Callback	�R�[���o�b�N�֐� [ void Callback( map::iterator& It, map& Map ) ]
			@retval	true	�v�f����������
			@retval	false	�v�f��������Ȃ�����
		 */
		template < typename TContainer, typename TCallbackFunc >
		inline static bool Find( TContainer& Cont,
								 const typename TContainer::key_type& Key,
								 TCallbackFunc Callback )
		{
			auto it = Cont.find( Key );
			if ( it == Cont.end() ) return false;

			// �R�[���o�b�N�֐������s
			Callback( it, Cont );
			return true;
		}

		/**
			@brief	�w��̃L�[�����v�f��T���A�폜�����s
			@param[in]	Cont	�R���e�i
			@param[in]	Key		�L�[
			@retval true	�v�f��������A�폜���s��ꂽ
			@retval false	�폜���s���Ȃ�����
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
