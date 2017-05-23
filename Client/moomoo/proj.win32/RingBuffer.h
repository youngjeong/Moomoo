#pragma once
#include<Windows.h>
#include<vector>

class RingBuffer
{
public:
	RingBuffer(size_t);
	int push(const char *, int);
	int pop(char*, int);
	int getbufSize();
	~RingBuffer();

private:
	void*				m_Q;
	int					m_size;
	int					m_head;
	int					m_tail;
	CRITICAL_SECTION	m_cs_read;
	CRITICAL_SECTION	m_cs_write;
};