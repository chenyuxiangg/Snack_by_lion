#include <ctime>
#include "snack.h"

Snack::Snack(int speed):m_speed(speed),m_radius(2)
{
	srand(time(0));
	m_col = RGB(rand()%255, (rand()%255+1)%255, (rand()%255+10)%255);

	m_head = new Snackpart();
	m_head->dir = dright;
	m_tail = m_head;
	
	setfillcolor(m_col);
	setlinecolor(m_col);
}

Snack::~Snack()
{
	Destroy(m_head);
}

void Snack::Destroy(Snackpart* head) {
	if (head != NULL) {
		Destroy(head->next);
	}
	delete head;
	head = NULL;
}

void Snack::Grow()
{
	Snackpart* part = new Snackpart();
	direction tmpdir = m_tail->dir;
	part->dir = tmpdir;
	switch (tmpdir) {
	case dright: {
		part->x = m_tail->x - 1;
		part->y = m_tail->y;
		break;
	}
	case dleft: {
		part->x = m_tail->x + 1;
		part->y = m_tail->y;
		break;
	}
	case dup: {
		part->x = m_tail->x;
		part->y = m_tail->y + 1;
		break;
	}
	case ddown: {
		part->x = m_tail->x;
		part->y = m_tail->y - 1;
		break;
	}
	default:
		break;
	}
	part->pre = m_tail;
	m_tail->next = part;
	part->next = NULL;
	m_tail = part;
}

void Snack::Draw()
{
	setfillcolor(m_col);
	setlinecolor(m_col);
	
	Snackpart* p = m_head;
	while (p != NULL) {
		if (p->x - 8 < 10 || p->x + 8 > 630 || p->y - 8 < 10 || p->y + 8 > 470) {
			break;
		}
		fillcircle(p->x, p->y, m_radius);
		p = p->next;
	}
}

void Snack::Move()
{
	Snackpart* p = m_tail;
	while (p != m_head) {
		direction dir = p->pre->dir;
		p->dir = p->pre->dir;
		p->x = p->pre->x;
		p->y = p->pre->y;
		p = p->pre;
	}

	direction head_dir = m_head->dir;
	switch (head_dir) {
		case dup:{
			m_head->y -= 1;
			break;
		}
		case ddown:{
			m_head->y += 1;
			break;
		}
		case dleft:{
			m_head->x -= 1;
			break;
		}
		case dright:{
			m_head->x += 1;
			break;
		}
		default:
			break;
	}
}
