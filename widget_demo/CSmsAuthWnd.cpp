#include "CSmsAuthWnd.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMovie>
#include "button.h"

#define SHADOW_RD 10
//内边距
#define MARGIN_LEN 2
#define TITLE_WND_HEIGHT 50
//主界面(不包括阴影)
#define MAIN_WND_WIDTH 604
#define MAIN_WND_HEIGHT 408
//内容界面
#define CONTENT_WND_WIDTH 600
#define CONTENT_WND_HEIGHT 356

#define CLOSE_BTN_THREE	"D:\\test\\qt\\Project1\\MsgWnd\\pwd_btn_close.png"

#define MAIN_WIDGET_STYLESHEET "QWidget#MainWnd{background:#026fbe;\
								padding: 0px; margin: 0px;}"
#define TITLE_WND_STYLESHEET "QWidget#TitleWnd{background:#026fbe;}"

#define CONTENT_WIDGET_STYLESHEET "QWidget#contentWnd{background:#FFFFFF;padding: 0px;margin: 0px; \
								border-style: solid; border-width: 1px; border-radius: 3px;\
								}"

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
					background:#026fbe;border-width: 0px;}"

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



CSmsAuthWnd::CSmsAuthWnd(QWidget* parent):QWidget(parent)
{
	initUI();
}
CSmsAuthWnd::~CSmsAuthWnd()
{

}

void CSmsAuthWnd::mousePressEvent(QMouseEvent* event)
{
	m_WindowPos = this->pos();
	m_mousePos = event->globalPos();
	m_DestPos = m_mousePos - m_WindowPos;
	m_bMove = m_mousePos.y() - m_WindowPos.y() < (28) ? true : false;
	qDebug() << "windows pos:" << m_WindowPos << "  mouse pos:" << m_mousePos << "\n";
}
void CSmsAuthWnd::mouseReleaseEvent(QMouseEvent* event)
{
	m_bMove = false;
}
void CSmsAuthWnd::mouseMoveEvent(QMouseEvent* event)
{
	if (m_bMove)
	{
		//qDebug() << "global pos:" << event->globalPos()<<",dest pos:"<< m_DestPos<<"\n";
		this->move(event->globalPos() - m_DestPos);
	}
}
void CSmsAuthWnd::closeEvent(QCloseEvent* event)
{
	event->accept();
	m_bShowWindow = false;
}
void CSmsAuthWnd::showEvent(QShowEvent* event)
{
	this->adjustSize();
	event->accept();
	m_bShowWindow = true;
}

void CSmsAuthWnd::MoveCenter()
{
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
	QDesktopWidget* desktop = QApplication::desktop();
	move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
#else
	QScreen* screen = QApplication::primaryScreen();
	move((screen->size().width() - this->width()) / 2, (screen->size().height() - this->height()) / 2);
#endif
}

void CSmsAuthWnd::initUI()
{
	//底层透明界面
	setObjectName("MyBaseWnd");
	setFixedSize(MAIN_WND_WIDTH + SHADOW_RD, MAIN_WND_HEIGHT + SHADOW_RD);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);

	//主窗体 界面 -》 标题界面 + 内容界面
	QWidget* m_MainWnd = new QWidget(this);
	m_MainWnd->setObjectName("MainWnd");
	m_MainWnd->setStyleSheet(MAIN_WIDGET_STYLESHEET);
	m_MainWnd->setMaximumSize(MAIN_WND_WIDTH, MAIN_WND_HEIGHT);

	QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
	shadowEffect->setColor(QColor(0, 0, 0, 30));
	shadowEffect->setBlurRadius(10);
	shadowEffect->setOffset(0, 0);
	m_MainWnd->setGraphicsEffect(shadowEffect);

	//标题界面
	QWidget *m_TitleWnd = new QWidget(m_MainWnd);
	m_TitleWnd->setObjectName("TitleWnd");
	m_TitleWnd->setFixedHeight(TITLE_WND_HEIGHT);
	m_TitleWnd->setStyleSheet(TITLE_WND_STYLESHEET);
	QHBoxLayout* hbTitleLayout = new QHBoxLayout(m_TitleWnd);
	
	m_labelTitle = new QLabel();
	m_labelTitle->setObjectName("title_text");
	m_labelTitle->setText(QString::fromLocal8Bit("入网身份认证"));
	m_labelTitle->setStyleSheet(TITLE_STYLE);
	m_btnClose = new Button(CLOSE_BTN_THREE, 3, this);
	m_btnClose->setStyleSheet("background: transparent");
	connect(m_btnClose, &Button::clicked, [this] {this->close(); });

	hbTitleLayout->addSpacing(248);
	hbTitleLayout->addWidget(m_labelTitle, Qt::AlignHCenter);
	hbTitleLayout->addStretch();
	hbTitleLayout->addWidget(m_btnClose, Qt::AlignRight);
	hbTitleLayout->addSpacing(2);

	
	QHBoxLayout* hbMainLayout = new QHBoxLayout(this);
	hbMainLayout->setMargin(0);
	QVBoxLayout* vbSubLayout = new QVBoxLayout(m_MainWnd);
	
	vbSubLayout->setMargin(2);
	vbSubLayout->addWidget(m_TitleWnd);
	vbSubLayout->setSpacing(0);

	//内容界面
	QWidget* pContentWnd = new QWidget(m_MainWnd);
	pContentWnd->setObjectName("contentWnd");
	pContentWnd->setMaximumSize(CONTENT_WND_WIDTH , CONTENT_WND_HEIGHT );
	pContentWnd->setStyleSheet(CONTENT_WIDGET_STYLESHEET);
	//sms
	QWidget* pMainContent = new QWidget(pContentWnd);
	int nHeight = pContentWnd->geometry().height();
	//pMainContent->setObjectName("mainSms");
	pMainContent->setFixedWidth(270);
	pMainContent->setMaximumHeight(CONTENT_WND_HEIGHT);
	pMainContent->setAttribute(Qt::WA_TranslucentBackground);
	//主体内容
	QVBoxLayout* vbSmsLayout = new QVBoxLayout(pMainContent);
	vbSmsLayout->setMargin(0);
	QLabel* pTips = new QLabel(pMainContent);
	//pTips->setObjectName("normal_text");
	pTips->setText(QString::fromLocal8Bit("为了验证您的身份，输入验证码后才能继续使用网络。"));
	pTips->setStyleSheet(NORMAL_TEXT_STYLE);
	pTips->setWordWrap(true);
	pTips->adjustSize();
	pTips->setContentsMargins(2, 0, 0, 0);
	pTips->setFixedSize(260, 45);

	QHBoxLayout* hbTips2 = new QHBoxLayout(pMainContent);
	//hbTips2->setContentsMargins(2, 0, 0, 0);
	QLabel* pTips_2 = new QLabel(QString::fromLocal8Bit("验证码已发送至："), pMainContent);
	//pTips_2->setObjectName("normal_text");
	pTips_2->setStyleSheet(NORMAL_TEXT_STYLE);
	pTips_2->setFixedSize(112, 20);
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

		//m_lbErrTips->setText("get code clicked...");
		m_lbErrTips->setText("");
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
		//this->repaint();
	});
	//btCheck->setDisabled(true);

	//vbSmsLayout->setContentsMargins(1, 0, 1, 10);
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

	//内容界面的布局
	QHBoxLayout* hbLayoutContent = new QHBoxLayout(pContentWnd);
	hbLayoutContent->setMargin(0);
	//
	hbLayoutContent->addSpacing(170);
	hbLayoutContent->addWidget(pMainContent, Qt::AlignCenter);
	hbLayoutContent->addStretch();
	//hbLayoutContent->addSpacing(170);

	vbSubLayout->addWidget(pContentWnd);
	//主界面 添加到 底层透明界面
	hbMainLayout->addWidget(m_MainWnd);
}

#define WAIT_WND_WIDTH 258
#define WAIT_WND_HEIGHT 94
//等待界面
#define WAIT_WND_STYLESHEET "QWidget{background:#FFFFFF;padding: 0px;margin: 0px; \
								border-width: 0px; border-radius: 3px;}"
#define TEXT_STYLE "QLabel{font-family: AlibabaPuHuiTiR; font-size: 14px; color:#4A4A4A;}"
#define GIF_PATH "D:\\test\\qt\\Project1\\MsgWnd\\wait_load.gif"

CWaitWnd::CWaitWnd(QWidget* parent)
{
	initUI();
}

CWaitWnd::~CWaitWnd()
{

}

void CWaitWnd::initUI()
{
	setObjectName("waitWnd");
	setFixedSize(WAIT_WND_WIDTH + SHADOW_RD, WAIT_WND_HEIGHT + SHADOW_RD);
	setWindowFlags(Qt::FramelessWindowHint |  Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	//setStyleSheet("QWidget#waitWnd{background:#FF00FF;}");

	QWidget* mainWnd = new QWidget(this);
	mainWnd->setFixedSize(WAIT_WND_WIDTH, WAIT_WND_HEIGHT);
	mainWnd->setMaximumSize(WAIT_WND_WIDTH, WAIT_WND_HEIGHT);
	mainWnd->setStyleSheet(WAIT_WND_STYLESHEET);

	QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
	shadowEffect->setColor(QColor(0, 0, 0, 30));
	shadowEffect->setBlurRadius(10);
	shadowEffect->setOffset(0, 0);
	mainWnd->setGraphicsEffect(shadowEffect);

	QHBoxLayout* hbLayout = new QHBoxLayout(mainWnd);
	hbLayout->setMargin(0);
	QVBoxLayout* vbLayout = new QVBoxLayout();
	vbLayout->setMargin(0);
	vbLayout->setSpacing(0);


	QLabel* lbImg = new QLabel();
	//lbImg->setStyleSheet("QLabel{background:#FF00FF;padding:0px;margin:0px}");
	lbImg->setMaximumSize(30,40);
	QHBoxLayout* hbImgLayout = new QHBoxLayout(mainWnd);
	hbImgLayout->setSpacing(0);
	hbImgLayout->addSpacing(114-74);
	hbImgLayout->addWidget(lbImg);
	hbImgLayout->addStretch();
	QMovie* pMv = new QMovie();
	pMv->setFileName(GIF_PATH);
	lbImg->setMovie(pMv);
	lbImg->adjustSize();
	pMv->start();

	QLabel* lbText = new QLabel();
	lbText->setStyleSheet(TEXT_STYLE);
	lbText->setFixedHeight(20);
	lbText->setText(QString::fromLocal8Bit("正在获取认证流程"));
	
	vbLayout->addSpacing(10);
	vbLayout->addLayout(hbImgLayout);
	vbLayout->addWidget(lbText, Qt::AlignCenter | Qt::AlignHCenter);
	vbLayout->addStretch();

	hbLayout->addSpacing(74);
	hbLayout->addLayout(vbLayout);
	hbLayout->addStretch();

	QHBoxLayout* hbTopLayout = new QHBoxLayout(this);
	hbTopLayout->setMargin(0);
	hbTopLayout->addWidget(mainWnd);
}