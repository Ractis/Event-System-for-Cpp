/* ------------------------------------------------------------------------- */
/*
 *  Ripple/Kernel/Events/EventDispatcherImpl.h
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

#ifndef ___RIPPLE_KERNEL_EVNETS_EVENTDISPATCHERIMPL_H___
#define ___RIPPLE_KERNEL_EVENTS_EVENTDISPATCHERIMPL_H___

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#include <Ripple/Kernel/Events/EventTraits.h>
#include <Ripple/Kernel/Utils/MapUtils.h>
#include <boost/noncopyable.hpp>
#include <boost/unordered_set.hpp>
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
		@brief	�C�x���g�f�B�X�p�b�`��
		@author	Ractis
	 */
	template < typename TEvent >
	class EventDispatcherImpl
		: private boost::noncopyable
	{
	public:
		typedef EventTraits<TEvent>			Traits;
		typedef typename Traits::TNameValue	TNameValue;	///< �C�x���g���ʎq�̌^
		typedef typename Traits::TNameParam	TNameParam;	///< �C�x���g���ʎq�p�����[�^�̌^
		typedef typename Traits::TListener	TListener;	///< �C�x���g���X�i�[�̌^

	private:
		typedef boost::unordered_set< TListener, typename TListener::Hash, typename TListener::EqualTo >	TListenerSet;
		typedef boost::unordered_map< TNameValue, TListenerSet >											TListenerCont;

	private:
		TListenerCont	m_ListenerCont;

	public:
		virtual ~EventDispatcherImpl() { }

		/**
			@brief	�C�x���g���X�i�[��ǉ�
			@param[in]	Name		�C�x���g��
			@param[in]	Listener	���X�i�[
		 */
		void AddEventListener( TNameParam Name, const TListener& Listener )
		{
			m_ListenerCont[Name].insert( Listener );
		}

		/**
			@brief	�C�x���g���X�i�[���폜
			@param[in]	Name		�C�x���g��
			@param[in]	Listener	���X�i�[
		 */
		void RemoveEventListener( TNameParam Name, const TListener& Listener )
		{
			// �w��̃C�x���g���̃��X�i�[�Z�b�g������
			Utils::MapUtils::Find( m_ListenerCont, Name, [&Listener]( typename TListenerCont::iterator& It, TListenerCont& )
			{
				// ���X�i�[���폜
				Utils::MapUtils::Erase( It->second, Listener );

				// ��ɂȂ��� Set ���̂� Map ����폜 (�������ߖ�)
				//if ( It->second.empty() ) m_ListenerCont.erase( It );
			} );
		}

		/**
			@brief	Event�𑗏o
			@retval	true	����ɑ��o���ꂽ���A�C�x���g���X�i�[������
			@retval	false	���o�Ɏ��s����
		 */
		bool DispatchEvent( TEvent& Evt )
		{
			// �w��̃C�x���g���̃��X�i�[�Z�b�g������
			Utils::MapUtils::Find( m_ListenerCont, Evt.Name(),
								   [&Evt]( typename TListenerCont::iterator& It, TListenerCont& )
			{
				// ���X�i�[�Z�b�g�ɓo�^����Ă��郊�X�i�[���A���ԂɌĂяo��
				BOOST_FOREACH ( const TListener& Listener, It->second )
				{
					Listener( Evt );
				}
			} );

			return true;
		}
	};

}
}
}

#endif // ___RIPPLE_KERNEL_EVNETS_EVENTDISPATCHERIMPL_H___
