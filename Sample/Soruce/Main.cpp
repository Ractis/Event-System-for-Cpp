
//================================================================================================================================
//
//================================================================================================================================
#include <Local/PCH.h>

//================================================================================================================================
//
//================================================================================================================================
using Ripple::Events::Event;

/**
	@brief	�C�x���g�̃J�X�^���N���X���̂P
	@author	Ractis
 */
class MsgEvent
	: public Event
{
private:
	const std::string& m_msg;

public:
	MsgEvent( Event::TNameParam Name, const std::string& Msg )
		: Event	( Name )
		, m_msg	( Msg )
	{
		std::cout << "[MSG EVT] \"" << Name << "\" is dispatched." << std::endl;
	}

	inline const std::string& msg() const { return m_msg; }
};

/**
	@brief	�C�x���g�̃J�X�^���N���X���̂Q
	@author	Ractis
 */
class IntEvent
	: public Ripple::Events::Event
{
private:
	int m_val;

public:
	IntEvent( Event::TNameParam Name, int val )
		: Event	( Name )
		, m_val	( val )
	{
		std::cout << "[INT EVT] \"" << Name << "\" is dispatched." << std::endl;
	}

	inline int val() const { return m_val; }
};

RIPPLE_DECL_EVENTTYPES( MsgEvent )
RIPPLE_DECL_EVENTTYPES( IntEvent )

//================================================================================================================================
//
//================================================================================================================================
/**
	@brief	2 ��ނ̃C�x���g��ʒm����N���X
	@author	Ractis
 */
class SampleEventManager
	: public Ripple::Events::EventDispatcher< MsgEvent, IntEvent >
{
};

typedef std::shared_ptr<SampleEventManager>	SPSampleEventManager;

//================================================================================================================================
//
//================================================================================================================================
/**
	@brief	MsgEvent �� Listen ����N���X
	@author	Ractis
 */
class MsgListener
{
private:
	MsgEventSmartListener	m_SmartListener;

private:
	// ���X�i�[
	void OnMessage( MsgEvent& evt )
	{
		// ���b�Z�[�W��\��
		std::cout << "  - [MsgListener] " << evt.msg() << std::endl;
	}

public:
	MsgListener( SPMsgEventDispatcher pDispar )
		: m_SmartListener ( MsgEventListener( this, &MsgListener::OnMessage ), pDispar, "Message" )
	{
	}
};

/**
	@brief	IntEvent �� Listen ����N���X
	@author	Ractis
 */
class IntListener
{
private:
	IntEventSmartListener	m_SmartListener;

private:
	// ���X�i�[
	void OnInteger( IntEvent& evt )
	{
		// ������\��
		std::cout << "  - [IntListener] " << evt.val() << std::endl;
	}

public:
	IntListener( SPIntEventDispatcher pDispar )
		: m_SmartListener ( IntEventListener( this, &IntListener::OnInteger ), pDispar, "Integer" )
	{
	}
};

/**
	@brief	MsgEvent �� IntEvent ������ Listenr ����N���X
	@author	Ractis
 */
class SampleListener
{
private:
	SPSampleEventManager	m_pMngr;
	MsgEventSmartListener	m_MessageLsnr;
	// IntEvent �͎蓮�œo�^���Ă݂�

private:
	// ���X�i�[
	void OnMessage( MsgEvent& evt )
	{
		// ���b�Z�[�W��\��
		std::cout << "  - [SampleListener] " << evt.msg() << std::endl;
	}

	void OnInteger( IntEvent& evt )
	{
		// ������\��
		std::cout << "  - [SampleListener] " << evt.val() << std::endl;
	}

public:
	SampleListener( SPSampleEventManager pMngr )
		: m_pMngr		( pMngr )
		, m_MessageLsnr	( MsgEventListener( this, &SampleListener::OnMessage ), *pMngr, "Message" )
	{
		// �蓮�œo�^����ꍇ�́AActionScript3.0 ���ۂ������� OK
		m_pMngr->AddEventListener( "Integer", IntEventListener( this, &SampleListener::OnInteger ) );
	}

	~SampleListener()
	{
		// AS3 �ł��߂�ǂ�������ˁI
		m_pMngr->RemoveEventListener( "Integer", IntEventListener( this, &SampleListener::OnInteger ) );
	}
};

//================================================================================================================================
//
//================================================================================================================================
int main()
{
	using namespace std;

	auto mngr = make_shared<SampleEventManager>();

	MsgListener		lsnrA( *mngr );
	IntListener		lsnrB( *mngr );
	auto lsnrC = std::unique_ptr<SampleListener>( new SampleListener( mngr ) );

	// �C�x���g��΂��Ă݂�
	cout << "============================================================" << endl;
	mngr->DispatchEvent( MsgEvent( "Message", "�Ă��Ă�" ) );

	cout << "============================================================" << endl;
	mngr->DispatchEvent( IntEvent( "Integer", 5 ) );

	cout << "============================================================" << endl;
	mngr->DispatchEvent( MsgEvent( "Integer", "" ) );		// �C�x���g���������ł��A�C�x���g�̌^���Ⴄ�ꍇ�̓��b�X������Ȃ�

	cout << "============================================================" << endl;
	lsnrC.reset();	// lsnrC ��j��
	mngr->DispatchEvent( MsgEvent( "Message", "lsnrC ��j��" ) );

	cout << "============================================================" << endl;

	return 0;
}
