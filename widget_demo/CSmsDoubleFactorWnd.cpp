#include "CSmsDoubleFactorWnd.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QBitmap>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QBrush>
#include <QStyle>
#include <QStackedWidget>
#include "button.h"

#define SHADOW_RD 10
//内边距
#define MARGIN_LEN 2
//主界面(不包括阴影)
#define MAIN_WND_WIDTH 604
#define MAIN_WND_HEIGHT 408
//内容界面
#define CONTENT_WND_WIDTH 600
#define CONTENT_WND_HEIGHT 356

#define CLOSE_BTN_THREE	"H:\\code\\1-qt\\my-qt-demo\\widget_demo\\pwd_btn_close.png"
//026fbe

#define NORMAL_BKG "QWidget{background:#026fbe;}"
								
#define MAIN_WIDGET_STYLESHEET2	"QWidget{box-shadow: 0 0 10px rgba(0, 0, 0, 0.3);\
								background:#026fbe; \
								}"
								
#define MAIN_WIDGET_STYLESHEET "QWidget#MainWnd{background:#026fbe;}"
#define TITLE_WND_STYLESHEET "QWidget#TitleWnd{background:#ff0000;}"
//#define TITLE_WND_STYLESHEET "QWidget#TitleWnd{background:#026fbe;}"

#define CONTENT_WIDGET_STYLESHEET "QWidget{background:#FFFFFF;padding: 0px; \
								border-radius: 3px;\
								}"
#define SMS_WIDGET_STYLESHEET "QWidget#mainSms{background:#00FFFF; \
								border-radius: 3px; padding: 0px;\
								}"
//透明顶层窗口
#define TOP_WND_STYLE "QWidget#MyBaseWnd{background:#026fbe;background-color: rgba(255, 255, 255, 50%); }"

#define button_stylesheet	"\
				QPushButton{\
				background:rgb(255,255,255);\
				border-style: solid;\
				border-width: 1px;\
				border-radius: 3px;\
				border-color: rgb(2,111,190);\
				color:rgb(80,80,80);\
				padding: 1px;\
				}\
				\
				QPushButton::hover{\
				background:rgb(203,244,248);\
				border-color:rgb(140,177,193);\
				color:rgb(80,80,80);\
				border-radius:3px;\
				}\
				\
				QPushButton::pressed{\
				background: rgb(127,255,254);\
				border-color: rgb(104,180,196);\
				border-radius: 3px;}"

#define CHECK_BT_STYLE "QPushButton{\
				background:#FFFFFF;\
				border-style: solid;\
				border-width: 1px;\
				border-radius: 3px;\
				border-color: #36A1EF;\
				padding: 1px;\
				}"
//验证按钮
#define NORMAL_CHECK_BT_STYLE "QPushButton{ background:#36A1EF;\
				font-family: AlibabaPuHuiTiR; font-size: 16px; color:#FFFFFF;\
				border-width: 0px;\
				border-radius: 3px;\
				padding: 1px;\
				}"
#define DISABLE_CHECK_BT_STYLE "QPushButton{ background:#EEEEEE ;\
				font-family: AlibabaPuHuiTiR; font-size: 14px; color:#999999;\
				border-width: 0px;\
				border-radius: 3px;\
				padding: 1px;\
				}"

#define TITLE_STYLE "QLabel#title_text{font-family: AlibabaPuHuiTiM; font-size: 16px; color:#ffffff;\
					background:#ff00ff;border-width: 0px;}"

#define PHONE_NUM_STYLE "QLabel#phone_text{color:#026fbe;\
					font-size: 16px;\
					font-family: AlibabaPuHuiTiM;\
					border-width: 0px;}"
#define NORMAL_TEXT_STYLE "QLabel{color:#999999;\
					font-size: 14px;\
					font-family: AlibabaPuHuiTiR;\
					border-width: 0px; padding: 0px;}"
#define ACTIVE_TEXT_STYLE "QLabel#active_text{color:#36A1EF;\
					font-size: 14px;\
					font-family: AlibabaPuHuiTiR;\
					border-width: 0px; padding: 0px;}"
#define ERR_TIP_STYLE "QLabel#err_tip{color:#FD393A;\
					font-size: 12px; line-height: 18px;\
					font-family: AlibabaPuHuiTiR;}"
#define ERR_TIP_STYLE_2 "QLabel#err_tip{color:#999999;\
					font-size: 12px; line-height: 18px;\
					font-family: AlibabaPuHuiTiR;}"
//获取验证码
#define GET_CODE_BUTTON	"QPushButton{ background:rgb(255,255,255);\
				border-style: solid; border-width: 1px; border-radius: 3px; border-color: #36A1EF;\
				font-family: AlibabaPuHuiTiR; font-size: 14px; color:#36A1EF;}"
#define DISABLE_GET_CODE_BUTTON	"QPushButton{ background:#F4F4F4;\
				border-style: solid; border-width: 1px; border-radius: 3px; border-color:#D5D5D5;\
				font-family: AlibabaPuHuiTiR; font-size: 14px; color:#999999;}"

#define NORMAL_LINE_EDIT "QLineEdit { background: #FFFFFF; \
								border-style: solid; border-width: 1px; border-color: #D5D5D5;\
								color:#999999;\
							   border-radius: 3px;}"

CMyBaseWnd::CMyBaseWnd(QWidget* contWnd,QWidget* parent):QWidget(parent), m_stackWidget(nullptr), m_ContentWnd(contWnd),
m_TitleWnd(nullptr),m_nWidth(MAIN_WND_WIDTH), m_nHeight(MAIN_WND_HEIGHT), m_labelTitle(nullptr),m_myClose(nullptr)
{
	setTitleWndHeight(50);
	initUI0();
}
CMyBaseWnd::~CMyBaseWnd()
{

}
void CMyBaseWnd::mousePressEvent(QMouseEvent* event)
{
	m_WindowPos = this->pos();
	m_mousePos = event->globalPos();
	m_DestPos = m_mousePos - m_WindowPos;
	m_bMove = m_mousePos.y() - m_WindowPos.y() < (28) ? true : false;
	qDebug() << "windows pos:" << m_WindowPos << "  mouse pos:" << m_mousePos << "\n";
}
void CMyBaseWnd::mouseReleaseEvent(QMouseEvent* event)
{
	m_bMove = false;
}
void CMyBaseWnd::mouseMoveEvent(QMouseEvent* event)
{
	if (m_bMove)
	{
		//qDebug() << "global pos:" << event->globalPos()<<",dest pos:"<< m_DestPos<<"\n";
		this->move(event->globalPos() - m_DestPos);
	}
}
void CMyBaseWnd::closeEvent(QCloseEvent* event)
{
	event->accept();
	m_bShowWindow = false;
	//QApplication::destroyed();
}
void CMyBaseWnd::showEvent(QShowEvent* event)
{
	this->adjustSize();
	event->accept();
	m_bShowWindow = true;
}

bool CMyBaseWnd::eventFilter(QObject *obj, QEvent *event)
{
	if ( event->type() == QEvent::MouseButtonPress)
	{
		qDebug() << "Mouse Press Event on PushButton";
	}

	// 其他事件过滤逻辑

	// 调用父类的事件过滤器
	return QObject::eventFilter(obj, event);
}

void CMyBaseWnd::setClose(closeFunc cFunc)
{
	m_myClose = cFunc;
	connect(m_btnClose, &Button::clicked, [ this] {
		if (!m_myClose)
		{
			m_myClose = std::bind(&CMyBaseWnd::close, this);
		}
		m_myClose();
	});
}

void CMyBaseWnd::setTitle(const std::string& strTitle)
{
	if (!m_labelTitle)
	{
		m_labelTitle = new QLabel();
	}
	m_labelTitle->setObjectName("title_text");
	//m_labelTitle->setText(QString::fromStdString(strTitle));
	m_labelTitle->setText(QString::fromLocal8Bit(strTitle.c_str()));
	m_labelTitle->setStyleSheet(TITLE_STYLE);
	
}
void CMyBaseWnd::addContentWnd(QWidget* pWnd)
{
	m_ContentWnd = pWnd;
}

void CMyBaseWnd::initUI0()
{
	setObjectName("MyBaseWnd");
	setFixedSize(m_nWidth+ SHADOW_RD, m_nHeight+ SHADOW_RD);
	//setWindowOpacity(0);
	//setStyleSheet(TOP_WND_STYLE);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	//setAttribute(Qt::WA_TranslucentBackground);
	//主窗体
	m_MainWnd = new QWidget(this);
	m_MainWnd->setObjectName("MainWnd");
	m_MainWnd->setStyleSheet(MAIN_WIDGET_STYLESHEET);
	m_MainWnd->setMaximumSize(m_nWidth, m_nHeight);

	//阴影
	QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
	shadowEffect->setColor(QColor(0, 0, 0, 30));
	shadowEffect->setBlurRadius(10);
	shadowEffect->setOffset(0, 0);
	m_MainWnd->setGraphicsEffect(shadowEffect);

	//标题界面
	if (m_TitleWnd == nullptr)
	{
		m_TitleWnd = new QWidget(m_MainWnd);
	}
	m_TitleWnd->setObjectName("TitleWnd");
	m_TitleWnd->setFixedHeight(nTitleWndHeight);
	m_TitleWnd->setStyleSheet(TITLE_WND_STYLESHEET);
	QHBoxLayout* hbTitleLayout = new QHBoxLayout(m_TitleWnd);
	setTitle("入网身份认证");
	m_btnClose = new Button(CLOSE_BTN_THREE, 3, this);
	m_btnClose->setStyleSheet("background: transparent");
	connect(m_btnClose, &Button::clicked, [this] {this->close(); });

	hbTitleLayout->addSpacing(248);
	hbTitleLayout->addWidget(m_labelTitle,Qt::AlignHCenter);
	hbTitleLayout->addStretch();
	hbTitleLayout->addWidget(m_btnClose, Qt::AlignRight);
	hbTitleLayout->addSpacing(2);

	//
	//QHBoxLayout* hbMainLayout = new QHBoxLayout(this);
	//QVBoxLayout* vbSubLayout = new QVBoxLayout(m_MainWnd);
	////m_TitleWnd->setMaximumHeight(nTitleWndHeight);
	////vbSubLayout->setContentsMargins(2, 2, 2, 2);
	//vbSubLayout->setMargin(12);
	//vbSubLayout->addWidget(m_TitleWnd);
	//vbSubLayout->setSpacing(0);
	//m_stackWidget = new QStackedWidget(m_MainWnd);
	//m_stackWidget->setMaximumSize(CONTENT_WND_WIDTH, CONTENT_WND_HEIGHT);
	//vbSubLayout->addWidget(m_stackWidget);
	//if (m_ContentWnd != nullptr)
	//{
	//	m_stackWidget->addWidget(m_ContentWnd);
	//	m_stackWidget->setCurrentWidget(m_ContentWnd);
	//	/*m_ContentWnd->setParent(m_MainWnd);
	//	m_ContentWnd->setMaximumSize(CONTENT_WND_WIDTH , CONTENT_WND_HEIGHT );
	//	vbSubLayout->addWidget(m_ContentWnd);*/
	//}
	//else
	//{
	//	QWidget* subWnd = new QWidget();
	//	subWnd->setStyleSheet(CONTENT_WIDGET_STYLESHEET);
	//	subWnd->setParent(this);
	//	//subWnd->setFixedSize(m_nWidth, m_nHeight- nTitleWndHeight);
	//	vbSubLayout->addWidget(subWnd);
	//}
	////m_MainWnd->setLayout(vbSubLayout);
	//hbMainLayout->addWidget(m_MainWnd);
}

void CMyBaseWnd::initUI(QWidget* subWnd)
{
	QHBoxLayout* hbMainLayout = new QHBoxLayout(this);
	hbMainLayout->setMargin(MARGIN_LEN);
	//m_MainWnd->setContentsMargins(2, 2, 2, 2);
	QVBoxLayout* vbSubLayout = new QVBoxLayout(m_MainWnd);
	//vbSubLayout->setMargin(1);
	//vbSubLayout->setContentsMargins(2, 2, 2, 2);
	vbSubLayout->addWidget(m_TitleWnd);
	vbSubLayout->setSpacing(0);
	if (subWnd != nullptr)
	{
		subWnd->setParent(this);
		subWnd->setMaximumSize(CONTENT_WND_WIDTH , CONTENT_WND_HEIGHT );
		//subWnd->setFixedSize(CONTENT_WND_WIDTH, CONTENT_WND_HEIGHT);
		vbSubLayout->addWidget(subWnd);
	}
	else
	{
		QWidget* subWnd = new QWidget(this);
		subWnd->setStyleSheet(CONTENT_WIDGET_STYLESHEET);
		subWnd->setFixedSize(CONTENT_WND_WIDTH, CONTENT_WND_HEIGHT);
		QHBoxLayout* hLayout = new QHBoxLayout(subWnd);
		QLineEdit* pedit = new QLineEdit(subWnd);
		pedit->setText("test...hello");
		pedit->setFixedSize(100, 20);
		hLayout->addWidget(pedit);

		vbSubLayout->addWidget(subWnd);
	}
	m_MainWnd->setLayout(vbSubLayout);
	hbMainLayout->addWidget(m_MainWnd);
	//setLayout(hbMainLayout);
}

void CMyBaseWnd::setWndSize(int nWidth, int nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

void CMyBaseWnd::setTitleWndHeight(int nHeight)
{
	nTitleWndHeight = nHeight;
}

void CMyBaseWnd::MoveCenter()
{
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
	QDesktopWidget* desktop = QApplication::desktop();
	move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
#else
	QScreen* screen = QApplication::primaryScreen();
	move((screen->size().width() - this->width()) / 2, (screen->size().height() - this->height()) / 2);
#endif
}

CSmsDoubleFactorWnd::CSmsDoubleFactorWnd(QWidget* parent):QWidget(parent)
{
	initUI2();
	//initUI(this);
	//setClose(std::bind(&CSmsDoubleFactorWnd::close, this));
}

CSmsDoubleFactorWnd::~CSmsDoubleFactorWnd()
{

}

//bool CSmsDoubleFactorWnd::close()
//{
//	qDebug() << "CSmsDoubleFactorWnd close..." << "\n";
//	return QWidget::close();
//	//return CMyBaseWnd::close();
//}

void CSmsDoubleFactorWnd::initUI2()
{
	//setFixedSize();
	setMaximumSize(CONTENT_WND_WIDTH, CONTENT_WND_HEIGHT);
	setStyleSheet(CONTENT_WIDGET_STYLESHEET);
	//sms
	QWidget* pMainContent = new QWidget(this);
	pMainContent->setObjectName("mainSms");
	pMainContent->setFixedSize(270, 356);
	pMainContent->setStyleSheet(SMS_WIDGET_STYLESHEET);
	//主体内容
	QVBoxLayout* vbSmsLayout = new QVBoxLayout(pMainContent);
	
	//vbSmsLayout->setAlignment(Qt::AlignCenter);

	QLabel* pTips = new QLabel(pMainContent);
	//pTips->setObjectName("normal_text");
	pTips->setText(QString::fromLocal8Bit("为了验证您的身份，输入验证码后才能继续使用网络。"));
	pTips->setStyleSheet(NORMAL_TEXT_STYLE);
	pTips->setWordWrap(true);
	pTips->adjustSize();
	pTips->setContentsMargins(2, 0, 0, 0);
	pTips->setFixedSize(260,45);

	QHBoxLayout* hbTips2 = new QHBoxLayout(pMainContent);
	//hbTips2->setContentsMargins(2, 0, 0, 0);
	QLabel* pTips_2 = new QLabel(QString::fromLocal8Bit("验证码已发送至："), pMainContent);
	//pTips_2->setObjectName("normal_text");
	pTips_2->setStyleSheet(NORMAL_TEXT_STYLE);
	pTips_2->setFixedSize(112,20);
	pTips_2->setContentsMargins(2, 0, 0, 0);

	m_lbPhoneNum = new QLabel(QString::fromLocal8Bit("***********"), pMainContent);
	m_lbPhoneNum->setObjectName("phone_text");
	m_lbPhoneNum->setStyleSheet(PHONE_NUM_STYLE);
	m_lbPhoneNum->setFixedHeight(20);
	hbTips2->addWidget(pTips_2);
	hbTips2->addWidget(m_lbPhoneNum);

	//获取验证码
	QHBoxLayout* hButtons = new QHBoxLayout(pMainContent);
	m_leCheckCode = new QLineEdit(QString::fromLocal8Bit("验证码"));
	m_leCheckCode->setStyleSheet(NORMAL_LINE_EDIT);
	m_leCheckCode->setFixedSize(130, 36);

	m_btGetCode = new QPushButton(QString::fromLocal8Bit("获取验证码"));
	m_btGetCode->setStyleSheet(GET_CODE_BUTTON);
	m_btGetCode->setFixedSize(120, 36);
	connect(m_btGetCode, &QPushButton::clicked, this, [=](bool bl) {
		qDebug() << "clicked:" << bl;
		m_btGetCode->setStyleSheet(DISABLE_GET_CODE_BUTTON);
		btCheck->setStyleSheet(QString(NORMAL_CHECK_BT_STYLE));
		m_lbErrTips->setStyleSheet(ERR_TIP_STYLE);
		
		m_lbErrTips->setText("get code clicked...");
		//this->resize(270, 356);
		//CMyBaseWnd::repaint();
	});

	//hButtons->setContentsMargins(1, 0, 0, 0);
	hButtons->setSpacing(0);
	hButtons->setAlignment(Qt::AlignCenter);
	hButtons->addWidget(m_leCheckCode);
	hButtons->addSpacing(10);
	hButtons->addWidget(m_btGetCode);
	hButtons->addStretch();

	//错误提示
	m_lbErrTips = new QLabel(QString::fromLocal8Bit("错误提示信息"), pMainContent);
	m_lbErrTips->setObjectName("err_tip");
	m_lbErrTips->setFixedSize(260, 18);
	m_lbErrTips->setStyleSheet(ERR_TIP_STYLE);
	connect(m_lbErrTips, &QLabel::hasFocus, this, [=]() {
		qDebug() << "hasFocus:";
		m_lbErrTips->setStyleSheet(QString(ERR_TIP_STYLE_2));
		//this->resize(270, 356);
	});

	//验证 按钮
	btCheck = new QPushButton(QString::fromLocal8Bit("验证"));
	btCheck->setStyleSheet(QString(NORMAL_CHECK_BT_STYLE));
	btCheck->setFixedSize(260, 36);
	connect(btCheck, &QPushButton::clicked, this, [=](bool bl) {
		qDebug() << "clicked:" << bl;	
		m_lbErrTips->setStyleSheet(QString(ERR_TIP_STYLE_2));
		btCheck->setStyleSheet(QString(DISABLE_CHECK_BT_STYLE));
		m_btGetCode->setStyleSheet(GET_CODE_BUTTON);
		m_lbErrTips->setText("btCheck clicked...");
		//btCheck->style()->polish(btCheck);
		this->repaint();
	});
	//btCheck->setDisabled(true);

	vbSmsLayout->setContentsMargins(1, 0, 1, 10);
	vbSmsLayout->setSpacing(0);
	vbSmsLayout->addSpacing(60);
	vbSmsLayout->addWidget(pTips);
	vbSmsLayout->addSpacing(5);
	vbSmsLayout->addLayout(hbTips2);
	vbSmsLayout->addSpacing(20);
	vbSmsLayout->addLayout(hButtons);
	vbSmsLayout->addSpacing(5);
	vbSmsLayout->addWidget(m_lbErrTips);
	vbSmsLayout->addSpacing(10);
	vbSmsLayout->addWidget(btCheck);
	vbSmsLayout->addStretch();
	pMainContent->setLayout(vbSmsLayout);

	QHBoxLayout* hbLayoutContent = new QHBoxLayout(this);
	hbLayoutContent->setMargin(0);
	//
	hbLayoutContent->addSpacing(170);
	hbLayoutContent->addWidget(pMainContent, Qt::AlignCenter);
	//hbLayoutContent->addStretch();
	hbLayoutContent->addSpacing(170);

	
	//this->setLayout(hbLayoutContent);
	//this->hide();
}
