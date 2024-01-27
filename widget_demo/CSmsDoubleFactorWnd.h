#ifndef _CSMSDOUBLEFACTORWND_H_
#define _CSMSDOUBLEFACTORWND_H_

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPoint>
#include <string>
#include <functional>

class QHBoxLayout;
class CMyBaseWnd;
using closeFunc = std::function<bool()>; //bool(CMyBaseWnd*)();

class CMyBaseWnd :public QWidget
{

	Q_OBJECT

public:
	CMyBaseWnd(QWidget* parent = Q_NULLPTR);
	~CMyBaseWnd();
	void mousePressEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void closeEvent(QCloseEvent* event)override;
	void showEvent(QShowEvent* event)override;
	void setWndSize(int nWidth, int nHeight);
	void setTitleWndHeight(int nHeight);
	void MoveCenter();
	void setTitle(const std::string& strTitle);
	void setClose(closeFunc close);
	void initUI(QWidget* subWnd = nullptr);
private:
	void initUI0();

protected:
	
	QWidget* m_TitleWnd;
	QWidget* m_MainWnd;
private:
	QWidget* m_ContentWnd; //内容窗口控件
	QPushButton* m_btnClose;			//关闭按钮
	QLabel* m_labelTitle;				//标题
	closeFunc m_myClose;
	int m_nWidth;
	int m_nHeight;
	int nTitleWndHeight;

	QPoint	m_WindowPos;	//窗口当前位置
	QPoint m_mousePos;		//鼠标位置
	QPoint m_DestPos;		//移动后所在位置
	bool m_bMove;
	bool m_bShowWindow;		//窗口已显示
};

class CSmsDoubleFactorWnd : public QWidget
{
public:
	CSmsDoubleFactorWnd(QWidget* parent = Q_NULLPTR);
	~CSmsDoubleFactorWnd();
	bool close();
private:
	void initUI2();

private:

	QLineEdit* m_leCheckCode;
	QPushButton* m_btGetCode;
	QPushButton* btCheck;
	QLabel* m_lbPhoneNum;				//手机号
	QLabel* m_lbErrTips;				//错误提示
};

#endif // !_CSMSDOUBLEFACTORWND_H_



