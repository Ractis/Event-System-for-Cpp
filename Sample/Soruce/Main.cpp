
//================================================================================================================================
//
//================================================================================================================================
#include <Local/PCH.h>

//================================================================================================================================
//
//================================================================================================================================
using Ripple::Events::Event;

/**
	@brief	イベントのカスタムクラスその１
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
	@brief	イベントのカスタムクラスその２
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
	@brief	2 種類のイベントを通知するクラス
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
	@brief	MsgEvent を Listen するクラス
	@author	Ractis
 */
class MsgListener
{
private:
	MsgEventSmartListener	m_SmartListener;

private:
	// リスナー
	void OnMessage( MsgEvent& evt )
	{
		// メッセージを表示
		std::cout << "  - [MsgListener] " << evt.msg() << std::endl;
	}

public:
	MsgListener( SPMsgEventDispatcher pDispar )
		: m_SmartListener ( MsgEventListener( this, &MsgListener::OnMessage ), pDispar, "Message" )
	{
	}
};

/**
	@brief	IntEvent を Listen するクラス
	@author	Ractis
 */
class IntListener
{
private:
	IntEventSmartListener	m_SmartListener;

private:
	// リスナー
	void OnInteger( IntEvent& evt )
	{
		// 数字を表示
		std::cout << "  - [IntListener] " << evt.val() << std::endl;
	}

public:
	IntListener( SPIntEventDispatcher pDispar )
		: m_SmartListener ( IntEventListener( this, &IntListener::OnInteger ), pDispar, "Integer" )
	{
	}
};

/**
	@brief	MsgEvent と IntEvent 両方を Listenr するクラス
	@author	Ractis
 */
class SampleListener
{
private:
	SPSampleEventManager	m_pMngr;
	MsgEventSmartListener	m_MessageLsnr;
	// IntEvent は手動で登録してみる

private:
	// リスナー
	void OnMessage( MsgEvent& evt )
	{
		// メッセージを表示
		std::cout << "  - [SampleListener] " << evt.msg() << std::endl;
	}

	void OnInteger( IntEvent& evt )
	{
		// 数字を表示
		std::cout << "  - [SampleListener] " << evt.val() << std::endl;
	}

public:
	SampleListener( SPSampleEventManager pMngr )
		: m_pMngr		( pMngr )
		, m_MessageLsnr	( MsgEventListener( this, &SampleListener::OnMessage ), *pMngr, "Message" )
	{
		// 手動で登録する場合は、ActionScript3.0 っぽい感じで OK
		m_pMngr->AddEventListener( "Integer", IntEventListener( this, &SampleListener::OnInteger ) );
	}

	~SampleListener()
	{
		// AS3 でもめんどくさいよね！
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

	// イベント飛ばしてみる
	cout << "============================================================" << endl;
	mngr->DispatchEvent( MsgEvent( "Message", "てすてす" ) );

	cout << "============================================================" << endl;
	mngr->DispatchEvent( IntEvent( "Integer", 5 ) );

	cout << "============================================================" << endl;
	mngr->DispatchEvent( MsgEvent( "Integer", "" ) );		// イベント名が同じでも、イベントの型が違う場合はリッスンされない

	cout << "============================================================" << endl;
	lsnrC.reset();	// lsnrC を破棄
	mngr->DispatchEvent( MsgEvent( "Message", "lsnrC を破棄" ) );

	cout << "============================================================" << endl;

	return 0;
}
