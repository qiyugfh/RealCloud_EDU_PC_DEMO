#include <Windows.h>
#include "WndList.h"
#include <QMessageBox>


int WndList::ms_nLastIndex = 0;

WndList::WndList(QWidget *parent/* = 0*/, Qt::WindowFlags f/* = 0*/)
	:QDialog(parent, f)
{
	m_ui.setupUi(this);
}

HWND WndList::GetSelectWnd(QWidget* parent /*= NULL*/)
{
	WndList* wndlist = new WndList(parent);
	int nRet = wndlist->Refresh();
	if (nRet != NO_ERR)
	{
		//AV_ERR_DEVICE_NOT_EXIST û�пɹ�����Ĵ���
		if (nRet == 1301)
		{
			QMessageBox::warning(parent, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("û�пɹ�����Ĵ���"), QMessageBox::Ok);
		}
		else
		{
			QMessageBox::warning(parent, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡ�����б�ʧ��"), QMessageBox::Ok);
		}
	}
	else
	{
		wndlist->exec();
	}
	HWND hwnd = wndlist->m_curhwnd;
	delete wndlist;
	return hwnd;
}

int WndList::Refresh()
{
	m_curhwnd = NULL;
	m_ui.liWndList->clear();
	int nRet = GetILive()->getWndList(m_wndList);
	if (nRet == NO_ERR)
	{
		for (int i = 0; i < m_wndList.size(); ++i)
		{
			m_ui.liWndList->addItem(new QListWidgetItem(QString::fromLocal8Bit(m_wndList[i].second.c_str())));
		}
		ms_nLastIndex = iliveMin(m_wndList.size() - 1, iliveMax(0, ms_nLastIndex));
		m_ui.liWndList->setCurrentRow(ms_nLastIndex);
	}
	return nRet;
}

void WndList::on_btnOK_clicked()
{
	ms_nLastIndex = m_ui.liWndList->currentRow();
	m_curhwnd = m_wndList[ms_nLastIndex].first;
	close();
}

void WndList::on_btnCancel_clicked()
{
	close();
}

void WndList::on_liWndList_itemDoubleClicked(QListWidgetItem* item)
{
	ms_nLastIndex = m_ui.liWndList->currentRow();
	m_curhwnd = m_wndList[ms_nLastIndex].first;
	close();
}
