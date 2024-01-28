#ifndef _CSMSAUTHWND_H_
#define _CSMSAUTHWND_H_

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPoint>
#include <QMouseEvent>

class CSmsAuthWnd :public QWidget
{

	Q_OBJECT

public:
	CSmsAuthWnd(QWidget* parent = Q_NULLPTR);
	~CSmsAuthWnd();

	void MoveCenter();

public:
	void mousePressEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void closeEvent(QCloseEvent* event)override;
	void showEvent(QShowEvent* event)override;

private:
	void initUI();
private:
	QPushButton* m_btnClose;			//关闭按钮
	QLabel* m_labelTitle;				//标题
	QLineEdit* m_leCheckCode;
	QPushButton* m_btGetCode;
	QPushButton* btCheck;
	QLabel* m_lbPhoneNum;				//手机号
	QLabel* m_lbErrTips;				//错误提示

	QPoint	m_WindowPos;	//窗口当前位置
	QPoint m_mousePos;		//鼠标位置
	QPoint m_DestPos;		//移动后所在位置
	bool m_bMove;
	bool m_bShowWindow;		//窗口已显示
};

#endif