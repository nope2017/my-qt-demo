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
	QPushButton* m_btnClose;			//�رհ�ť
	QLabel* m_labelTitle;				//����
	QLineEdit* m_leCheckCode;
	QPushButton* m_btGetCode;
	QPushButton* btCheck;
	QLabel* m_lbPhoneNum;				//�ֻ���
	QLabel* m_lbErrTips;				//������ʾ

	QPoint	m_WindowPos;	//���ڵ�ǰλ��
	QPoint m_mousePos;		//���λ��
	QPoint m_DestPos;		//�ƶ�������λ��
	bool m_bMove;
	bool m_bShowWindow;		//��������ʾ
};

#endif