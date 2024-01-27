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
	QWidget* m_ContentWnd; //���ݴ��ڿؼ�
	QPushButton* m_btnClose;			//�رհ�ť
	QLabel* m_labelTitle;				//����
	closeFunc m_myClose;
	int m_nWidth;
	int m_nHeight;
	int nTitleWndHeight;

	QPoint	m_WindowPos;	//���ڵ�ǰλ��
	QPoint m_mousePos;		//���λ��
	QPoint m_DestPos;		//�ƶ�������λ��
	bool m_bMove;
	bool m_bShowWindow;		//��������ʾ
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
	QLabel* m_lbPhoneNum;				//�ֻ���
	QLabel* m_lbErrTips;				//������ʾ
};

#endif // !_CSMSDOUBLEFACTORWND_H_



