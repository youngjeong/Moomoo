#include "RingBuffer.h"
#include<memory.h>
#include<vector>


RingBuffer::RingBuffer(size_t buf_size) :
	m_head(0), m_tail(0)
{

	::InitializeCriticalSection(&m_cs_read);

	m_Q = (char*)malloc(buf_size);
	memset(m_Q, 0, sizeof(m_Q));
	m_size = buf_size;

	::InitializeCriticalSection(&m_cs_write);
}
int RingBuffer::push(const char *data, int data_size)
{
	::EnterCriticalSection(&m_cs_write);

	int ret = 0;
	if (m_tail < m_head && m_tail + data_size >= m_head)ret - 1;
	else if (m_size - m_tail < data_size) // overhead
	{
		int remain = data_size - (m_size - m_tail);
		if (remain >= m_head) {
			ret = -1; // impossible to push (full)
		}
		else {
			memcpy(&m_Q + m_tail, data, (m_size - m_tail));
			memcpy(&m_Q, data + (m_size - m_tail + 1), remain);
			m_tail = remain;
		}
	}
	else
	{
		memcpy(&m_Q + m_tail, data, data_size);
		m_tail += data_size;
	}
	
	::LeaveCriticalSection(&m_cs_write);
	return ret;

}

int RingBuffer::pop(char *data, int data_size)
{
	::EnterCriticalSection(&m_cs_read);

	int ret = 0;
	if (m_head < m_tail && m_head + data_size > m_tail)ret = 1;
	else if (m_head + data_size > m_size)
	{
		int remain = data_size - (m_size - m_head);
		if (remain >= m_tail) {
			ret = -1; // impossible to pop
		}
		else
		{
			memcpy(data, &m_Q + m_head, (m_size - m_head));
			memcpy(data + (m_size - m_head), &m_Q, remain);
			m_head = remain;
		}
	}
	else {
		memcpy(data, &m_Q + m_head, data_size);
		m_head += data_size;
	}
	return ret;

	::LeaveCriticalSection(&m_cs_read);
}

int RingBuffer::getbufSize()
{
	return m_size;
}
RingBuffer::~RingBuffer()
{
	::DeleteCriticalSection(&m_cs_read);
	::DeleteCriticalSection(&m_cs_write);
}
