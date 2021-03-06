
#ifndef kernal_h
#define kernal_h

#include "stdafx.h"
#include<vector>
//#include<Windows.h>

using namespace std;

//typedef wchar_t SICHAR_T;
typedef char SICHAR_T;
typedef LOGFONT SIFONT;
//void isenter(SICHAR_T);
/*
typedef struct tagLOGFONT
{ LONG lfHeight;
LONG lfWidth;
LONG lfEscapement;
LONG lfOrientation;
LONG lfWeight;
BYTE lfItalic;
BYTE lfUnderline;
BYTE lfStrikeOut;
BYTE lfCharSet;
BYTE lfOutPrecision;
BYTE lfClipPrecision;
BYTE lfQuality;
BYTE lfPitchAndFamily;
TCHAR lfFaceName[LF_FACESIZE];
} LOGFONT;
*/
typedef SIFONT* SIFONT_P;
typedef const SIFONT* SIFONT_PC;
typedef int COLORERF;
typedef int CHARSIZE;
typedef int CHARSPACE;
typedef int LINESPACE;
typedef int SIALIGN;

class SICHAR_INFO;
class SIDRAW_INFO;
class SICHARNODE;
class SITEXT;
struct SIRECT;
struct SIPOINT;
struct SIRANGE;
//struct SITEXT;



inline bool isenter(SICHAR_T ch)
{
	return ch == '\n' || ch == '\r';
}

inline int Max(int a, int b)
{
	return a > b ? a : b;
}



class SICHAR_INFO
{
private:
	//const SIFONT_P fontp;

public:
	SIFONT_PC fontpc;
	COLORERF color;
	CHARSIZE size;
	CHARSPACE cspace;
	LINESPACE lspace;
	SIALIGN align;

	friend class SICHARNODE;
	SICHAR_INFO() :fontpc(NULL)
	{
		//fontp = NULL;
		color = size = cspace = lspace = align = 0;
	}
	inline void set_fontpc(SIFONT_PC tfontpc);
	inline void set_fontpc(const SIFONT& tfont);
	inline void set_color(COLORERF tcolor);
	inline void set_size(CHARSIZE tsize);
	inline void set_cspace(CHARSPACE tcspace);
	inline void set_lspace(LINESPACE tlspace);
	///<interface>
	inline SIFONT_PC get_fontpc();
	inline COLORERF get_color();
	inline CHARSIZE get_size();
	///<interface>
	inline CHARSPACE get_cspace();
	inline LINESPACE get_lspace();
};
typedef SICHAR_INFO* SICHAR_INFO_P;

struct SIRECT
{
	int width;
	int height;
	SIRECT(int twidth = 15, int theight = 15)
	{
		width = twidth;
		height = theight;
	}
	void print()
	{
		printf("%d %d", width, height);
	}
};

struct SIPOINT
{
	int x;
	int y;
	SIPOINT(int tx = 0, int ty = 0)
	{
		x = tx; y = ty;
	}
	void print()
	{
		printf("%d %d", x, y);
	}
	friend SIPOINT operator + (const SIPOINT& A, const SIPOINT& B)
	{
		return SIPOINT(A.x + B.x, A.y + B.y);
	}
	friend SIPOINT operator - (const SIPOINT& A, const SIPOINT& B)
	{
		return SIPOINT(A.x - B.x, A.y - B.y);
	}
	friend bool operator < (const SIPOINT& A, const SIPOINT& B)
	{
		return	A.y < B.y ||
			A.y == B.y && (A.x < B.x);
	}
	friend bool operator > (const SIPOINT& A, const SIPOINT& B)
	{
		return B < A;
	}
};

class SIDRAW_INFO
{
private:

public:
	SIRECT S;		//small rectangle
	SIRECT L;		//large rectangle
	SIPOINT POS;	//coor. (left_top)

	friend class SICHARNODE;
	SIDRAW_INFO()
	{
		S = SIRECT(); L = SIRECT(); POS = SIPOINT();
	}
	SIDRAW_INFO(const SIRECT& TS, const SIRECT& TL, const SIPOINT& TPOS)
	{
		S = TS; L = TL; POS = TPOS;
	}
	inline void set_S(const SIRECT&);
	inline void set_L(const SIRECT&);
	inline void set_POS(const SIPOINT&);
	///<interface>
	inline const SIRECT& get_S();
	inline SIRECT& get_L();
	inline SIPOINT& get_POS();
	///<interface>
};
typedef SIDRAW_INFO* SIDRAW_INFO_P;

class SICHARNODE
{
private:

public:
	SICHAR_T ch;
	SICHAR_INFO_P char_infop;
	SIDRAW_INFO_P draw_infop;
	SICHARNODE *prevp;
	SICHARNODE *nextp;

	friend class SITEXT;
	SICHARNODE(SICHAR_T tch, SICHARNODE* tprevp = NULL, SICHARNODE* tnextp = NULL
		, SICHAR_INFO_P tchar_infop = NULL, SIDRAW_INFO_P tdraw_infop = NULL)
	{
		ch = tch;
		char_infop = new SICHAR_INFO;
		draw_infop = new SIDRAW_INFO;
		if (tchar_infop != NULL) *char_infop = *tchar_infop;
		if (tdraw_infop != NULL) *draw_infop = *tdraw_infop;
		prevp = tprevp;
		nextp = tnextp;
	}

	SICHARNODE(SICHAR_T tch, int tswidth, int tsheight)
	{
		ch = tch;
		char_infop = new SICHAR_INFO;
		draw_infop = new SIDRAW_INFO;
		draw_infop->S.width = tswidth;
		draw_infop->S.height = tsheight;
	}

	~SICHARNODE()
	{
		if (char_infop != NULL) delete char_infop;
		if (draw_infop != NULL) delete draw_infop;
	}
	inline void set_fontpc(SIFONT_PC tfontpc);
	inline void set_fontpc(const SIFONT& tfont);
	inline void set_color(COLORERF tcolor);
	inline void set_size(CHARSIZE tsize);
	//	inline void set_char_infop(const SIFONT& tfont, COLORERF tcolor, CHARSIZE tsize);
	//	inline void set_char_infop(SIFONT_P tfontp, COLORERF tcolor, CHARSIZE tsize);
	inline void set_draw_infop_S(const SIRECT& TS);
	inline void set_draw_infop_L(const SIRECT& TL);
	inline void set_draw_infop_P(const SIPOINT& TP);
	//	inline void set_draw_infop_LP(const SIRECT& TL, const SIPOINT& TP);
	//	inline void set_draw_infop(const SIRECT& TS, const SIRECT& TL, const SIPOINT& TP);
	inline void ins_prev(SICHARNODE* p);
	inline void ins_next(SICHARNODE* p);
	inline void ins_prev(SICHARNODE* ps, SICHARNODE* pe);
	inline void ins_next(SICHARNODE* ps, SICHARNODE* pe);
	inline void ins_prev(const SIRANGE& range);
	inline void ins_next(const SIRANGE& range);
	friend void del(SICHARNODE* p);
	friend void del(SICHARNODE* ps, SICHARNODE* pe);
	friend void del(const SIRANGE& range);
	///<interface>
	inline const SICHAR_INFO_P get_char_infop();
	inline const SIDRAW_INFO_P get_draw_infop();
	///<\interface>

	void print()
	{
		//		SICHARNODE_P p = this;
		if (isenter(ch))
		{
			printf("ENTER\n");
			draw_infop->POS.print();
			printf("\n");
			draw_infop->L.print();
			printf("\n\n");
			return;
		}
		printf("%c\n", ch);
		//		p->draw_infop->POS->print();
		draw_infop->POS.print();
		printf("\n");
		draw_infop->L.print();
		printf("\n\n");

	}
};
typedef SICHARNODE* SICHARNODE_P;

struct SIRANGE
{
	SICHARNODE_P sp;
	SICHARNODE_P ep;
	SIRANGE(SICHARNODE_P tsp = NULL, SICHARNODE_P tep = NULL)
	{
		sp = tsp;
		ep = tep;
	}
	void _clear()
	{
		sp = ep = NULL;
	}
};
typedef SIRANGE SISELECT;
typedef SIRANGE SIPARAGRAPH;
typedef SIRANGE SILINE;

typedef int PAGEWIDTH;
typedef SICHARNODE_P SICURSORP;
typedef int SIDIRECT;
typedef int SIALIGN;
class SITEXT
{
private:
public:
	SICHARNODE_P headp;
	SICHARNODE_P tailp;

	SICURSORP cursorp;
	SISELECT select;

	PAGEWIDTH pagewidth;

	SIFONT_PC curfontpc;

	bool inselect;
	int fwdnum;
	std::vector<SILINE> vlinep;
	std::vector<SIPARAGRAPH> vparap;

	//set true when text changed specifically when \
				effectable methods are called		\
	  set false when repaint() is called
	bool text_changed_f;
	//set true when set_curfontp() is called \
			  set false when cursor moved
	bool set_curfontp_f;

private:

	inline void draw_line_from_left(SICHARNODE_P ps, SICHARNODE_P pe, int sx, int y, int line_height, int deltax);
	inline void proc_line(SICHARNODE_P ps, SICHARNODE_P pe, int n, int y, int line_height, int tot_weight, int align);
	inline void proc_text();
	inline void pre_proc();
public:

	static const PAGEWIDTH DEFAULT_PAGEWIDTH = 110;

	static const SIDIRECT DLEFT = 0;
	static const SIDIRECT DRIGHT = 1;
	static const SIDIRECT DUP = 2;
	static const SIDIRECT DDOWN = 3;

	static const SIALIGN ANORMAL = 0;
	static const SIALIGN ALEFT = 0;
	static const SIALIGN ARIGHT = 1;
	static const SIALIGN ACENTER = 2;
	static const SIALIGN ADISTRIBUTED = 3;

	//debug mod
	void print_cursorp()
	{
		cursorp->draw_infop->POS.print();
		printf("\n");
	}
	//end debug
	//constructor
	SITEXT();
	///<interface>
	//Operate method
	///inline void load();
	///inline void save();
	//	inline void _init();
	inline void ins_char(SICHAR_T);
	//debug mod?
	inline void ins_char(SICHAR_T, int, int);
	//------------
	inline void del_char(bool backwards);
	inline void start_select();
	inline void end_select();
	inline void del_select();
	inline void replace_select(const SIRANGE&);
	inline void replace_select(SICHARNODE_P ps, SICHARNODE_P pe);
	inline void cancel_select();
	inline void mov_select(SICURSORP);
	inline void mov_cursorp(SICURSORP);
	inline void mov_cursorp(SIDIRECT);
	inline void mov_cursorp(const SIPOINT&);
	///several set_* method
	inline void set_select_font(SIFONT_PC tfontpc);
	inline void set_select_font(const SIFONT& tfont);
	inline void set_curfont(SIFONT_PC tcurfontpc);
	inline void set_curfont(const SIFONT& tcurfont);
	inline void set_select_color(COLORERF tcolor);
	inline void set_select_lspace(LINESPACE tlspace);
	inline void set_select_cspace(CHARSPACE tcspace);
	inline void set_pagewidth(PAGEWIDTH tpagewidth);
	///several get_* method
	inline SICURSORP point_to_cursorp(const SIPOINT& P);
	//Draw method
	///cursor - coord transparent
	///divide line
	///line texing
	inline void repaint();
	void print_list();
	///<\interface>
};


//SICHAR_INFO
inline void SICHAR_INFO::set_fontpc(SIFONT_PC tfontp)
{
	fontpc = tfontp;
}
inline void SICHAR_INFO::set_fontpc(const SIFONT& tfont)
{
	fontpc = &tfont;
}
inline void SICHAR_INFO::set_color(COLORERF tcolor)
{
	color = tcolor;
}
inline void SICHAR_INFO::set_size(CHARSIZE tsize)
{
	size = tsize;
}
inline void SICHAR_INFO::set_cspace(CHARSPACE tcspace)
{
	cspace = tcspace;
}
inline void SICHAR_INFO::set_lspace(LINESPACE tlspace)
{
	lspace = tlspace;
}
inline SIFONT_PC SICHAR_INFO::get_fontpc()
{
	return fontpc;
}
inline COLORERF SICHAR_INFO::get_color()
{
	return color;
}
inline CHARSIZE SICHAR_INFO::get_size()
{
	return size;
}
inline CHARSPACE SICHAR_INFO::get_cspace()
{
	return cspace;
}
inline LINESPACE SICHAR_INFO::get_lspace()
{
	return lspace;
}

//SIDRAW_INFO
inline void SIDRAW_INFO::set_S(const SIRECT& TS)
{
	S = TS;
}
inline void SIDRAW_INFO::set_L(const SIRECT& TL)
{
	S = TL;
}
inline void SIDRAW_INFO::set_POS(const SIPOINT& TPOS)
{
	POS = TPOS;
}
inline const SIRECT& SIDRAW_INFO::get_S()
{
	return S;
}
inline SIRECT& SIDRAW_INFO::get_L()
{
	return L;
}
inline SIPOINT& SIDRAW_INFO::get_POS()
{
	return POS;
}
//SICHARNODE
inline void SICHARNODE::set_fontpc(SIFONT_PC tfontp)
{
	char_infop->set_fontpc(tfontp);
}
inline void SICHARNODE::set_fontpc(const SIFONT& tfont)
{
	char_infop->set_fontpc(tfont);
}
inline void SICHARNODE::set_color(COLORERF tcolor)
{
	char_infop->set_color(tcolor);
}
inline void SICHARNODE::set_size(CHARSIZE tsize)
{
	char_infop->set_size(tsize);
}
/*
inline void SICHARNODE::set_char_infop(const SIFONT& tfont, COLORERF tcolor, CHARSIZE tsize)
{
char_infop->set_fontpc(tfont);
char_infop->set_color(tcolor);
char_infop->set_size(tsize);
}
inline void SICHARNODE::set_char_infop(SIFONT_P tfontp, COLORERF tcolor, CHARSIZE tsize);
*/
inline void SICHARNODE::set_draw_infop_S(const SIRECT& TS)
{
	draw_infop->set_S(TS);
}
inline void SICHARNODE::set_draw_infop_L(const SIRECT& TL)
{
	draw_infop->set_L(TL);
}
inline void SICHARNODE::set_draw_infop_P(const SIPOINT& TP)
{
	draw_infop->set_POS(TP);
}
/**
inline void SICHARNODE::set_draw_infop_LP(const SIRECT& TL, const SIPOINT& TP);
inline void SICHARNODE::set_draw_infop(const SIRECT& TS, const SIRECT& TL, const SIPOINT& TP);
*/
inline void SICHARNODE::ins_prev(SICHARNODE* p)
{
	p->prevp = this->prevp;
	p->nextp = this;
	this->prevp->nextp = p;
	this->prevp = p;
}
inline void SICHARNODE::ins_next(SICHARNODE* p)
{
	p->prevp = this;
	p->nextp = this->nextp;
	this->nextp->prevp = p;
	this->nextp = p;
}
inline void SICHARNODE::ins_prev(SICHARNODE* ps, SICHARNODE* pe)
{
	ps->prevp = this->prevp;
	pe->nextp = this;
	this->prevp->nextp = ps;
	this->prevp = pe;
}
inline void SICHARNODE::ins_next(SICHARNODE* ps, SICHARNODE* pe)
{
	ps->prevp = this;
	pe->nextp = this->nextp;
	this->nextp->prevp = pe;
	this->nextp = ps;
}
inline void SICHARNODE::ins_prev(const SIRANGE& range)
{
	ins_prev(range.sp, range.ep);
}
inline void SICHARNODE::ins_next(const SIRANGE& range)
{
	ins_next(range.sp, range.ep);
}

///<interface>
inline const SICHAR_INFO_P SICHARNODE::get_char_infop()
{
	return char_infop;
}
inline const SIDRAW_INFO_P SICHARNODE::get_draw_infop()
{
	return draw_infop;
}
///<\interface>

//SITEXT
//const SIDIRECT SITEXT::LEFT = 0;
//const SIDIRECT SITEXT::RRIHT = 1;
//const SIDIRECT SITEXT::UP = 2;
//const SIDIRECT SITEXT::DOWN = 3;
///<private>
inline void SITEXT::draw_line_from_left(SICHARNODE_P ps, SICHARNODE_P pe, int sx, int y, int line_height, int deltax)
{
	int x;
	SICHARNODE_P p;
	SIDRAW_INFO_P pd;

	for (x = sx, p = ps; p != pe; p = p->nextp)
	{
		pd = p->draw_infop;
		pd->L.height = line_height;
		pd->L.width = pd->S.width + p->char_infop->cspace + deltax;
		pd->POS = SIPOINT(x, y);
		x += pd->L.width;
	}

}


inline void SITEXT::proc_line(SICHARNODE_P ps, SICHARNODE_P pe,
	int n, int y, int line_height, int tot_width, int align)
{
	int sx = 0, deltax = 0;

	if (align == ANORMAL || align == ALEFT)
	{
		//draw_line_from_left(ps, pe, 0, y, line_height, 0);
		sx = 0;
		deltax = 0;
	}
	if (align == ARIGHT)
	{
		//draw_line_from_left(ps, pe, pagewidth - tot_width, y, line_height, 0);
		sx = pagewidth - tot_width;
		deltax = 0;
	}
	if (align == ACENTER)
	{
		//draw_line_from_left(ps, pe, (pagewidth - tot_width) >> 1, y, line_height, 0);
		sx = (pagewidth - tot_width) >> 1;
		deltax = 0;
	}
	if (align == ADISTRIBUTED)
	{
		//draw_line_from_left(ps, pe, 0, y, line_height, (pagewidth - tot_width) / n);
		sx = 0;
		deltax = (pagewidth - tot_width) / n;
	}

	draw_line_from_left(ps, pe, sx, y, line_height, deltax);
	return;
}
inline void SITEXT::pre_proc()
{
	SICHARNODE_P p;
	for (p = headp->nextp; p != tailp; p = p->nextp)
	{
		if (isenter(p->ch) && isenter(p->nextp->ch))
		{
			p->ins_next(new SICHARNODE(' ', 0, p->draw_infop->S.height));
		}
	}
}
inline void SITEXT::proc_text()
{
	SICHARNODE_P ps, pe, pps;
	SIDRAW_INFO_P pd;
	SICHAR_INFO_P pc;
	int tot_width;
	int n;
	int line_height;
	int y;

	vlinep.clear();
	vparap.clear();

	for (y = 0, ps = headp->nextp, pps = headp; ps != tailp; ps = pe)
	{
		tot_width = 0;
		line_height = 0;
		n = 0;
		for (pe = ps; tot_width <= pagewidth && (!isenter(pe->ch)); pe = pe->nextp)
		{
			++n;
			pd = pe->draw_infop;
			pc = pe->char_infop;
			tot_width += (pd->S.width + pc->cspace);
			line_height = Max(line_height, pd->S.height + pc->lspace);
			if (tot_width > pagewidth) break;
		}
		--n;
		if (isenter(pe->ch) && pe != tailp)
		{
			vparap.push_back(SIPARAGRAPH(pps->nextp, pe));
			pps = pe;
			pe = pe->nextp;
		}
		vlinep.push_back(SILINE(ps, pe));
		proc_line(ps, pe, n, y, line_height, tot_width, ps->char_infop->align);
		y += line_height;
		if (pe == tailp)
		{
			tailp->draw_infop->POS = tailp->prevp->draw_infop->POS
				+ SIPOINT(tailp->prevp->draw_infop->L.width, 0);
			break;
		}
	}
}

///<\private>
//constructor

/*
///<interface>
//Operate method
///inline void load();
///inline void save();
inline void SITEXT::_init();
*/

template<class T>
void exchange(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

inline void SITEXT::ins_char(SICHAR_T tchar)
{
	cursorp->ins_prev(new SICHARNODE(tchar));
}

inline void SITEXT::ins_char(SICHAR_T ch, int twidth, int theight)
{
	ins_char(ch);
	cursorp->prevp->draw_infop->S.width = twidth;
	cursorp->prevp->draw_infop->S.height = theight;
}

inline void SITEXT::del_char(bool backwards = true)
{
	SICHARNODE_P prevp, pprevp, curp, nextp;
	prevp = cursorp->prevp;
	curp = cursorp;
	nextp = curp->nextp;
	if (backwards&&prevp != headp)
	{
		pprevp = prevp->prevp;
		if (prevp->draw_infop->S.width == 0 && pprevp != headp&&isenter(pprevp->ch))
			del(pprevp);
		del(prevp);
	}
	if ((!backwards) && nextp != NULL)
	{
		if (isenter(curp->ch) && nextp->draw_infop->S.width == 0)
			del(nextp);
		cursorp = cursorp->nextp;
		del(cursorp->prevp);
	}
}

inline void SITEXT::start_select()
{
	select.sp = cursorp;
	inselect = true;
	fwdnum = 0;
}

inline void SITEXT::end_select()
{
	select.ep = cursorp;
	if (select.sp->draw_infop->POS > select.ep->draw_infop->POS)
		exchange<SICHARNODE_P>(select.sp, select.ep);
	//if (fwdnum < 0) exchange<SICHARNODE_P>(select.sp, select.ep);
	//if (fwdnum == 0) select._clear();
	//inselect = false;
	//fwdnum = 0;
}

inline void SITEXT::cancel_select()
{
	select._clear();
}

inline void SITEXT::del_select()
{
	cursorp = select.ep;
	del(select.sp, select.ep);
	cancel_select();
}

inline void SITEXT::replace_select(SICHARNODE_P ps, SICHARNODE_P pe)
{
	SICHARNODE_P p = select.ep->nextp;
	del(select);
	p->ins_prev(ps, pe);
}

inline void SITEXT::replace_select(const SIRANGE& range)
{
	replace_select(range.sp, range.ep);
}

/*
inline void SITEXT::replace_select()
*/

inline void SITEXT::mov_select(SICURSORP tcursorp)
{
	select.sp->prevp->nextp = select.ep->nextp;
	select.ep->nextp->prevp = select.sp->prevp;
	tcursorp->ins_prev(select.sp, select.ep);
}


inline void SITEXT::mov_cursorp(SICURSORP tcursorp)
{
	cursorp = tcursorp;
}
inline void SITEXT::mov_cursorp(SIDIRECT tdir)
{
	switch (tdir)
	{
	case DLEFT:
		if (cursorp->prevp != headp)
		{
			cursorp = cursorp->prevp;
			if (cursorp->draw_infop->S.width == 0 && cursorp->prevp != headp && isenter(cursorp->prevp->ch))
				cursorp = cursorp->prevp;
		}
		break;
	case DRIGHT:
		if (cursorp->nextp != NULL)
		{
			cursorp = cursorp->nextp;
			if (cursorp->draw_infop->S.width == 0 && cursorp->nextp != NULL&&isenter(cursorp->prevp->ch))
				cursorp = cursorp->nextp;
		}
		break;
	case DUP:
		if (cursorp->draw_infop->POS.y != 0)
			cursorp = point_to_cursorp(cursorp->draw_infop->POS - SIPOINT(0, 1));
		break;
	case DDOWN:
		//if(cursorp->draw_infop->POS.y!=MAX_POSY)
		cursorp = point_to_cursorp(cursorp->draw_infop->POS + SIPOINT(0, cursorp->draw_infop->L.width + 2));
		break;
	}

}
inline void SITEXT::mov_cursorp(const SIPOINT& P)
{
	cursorp = point_to_cursorp(P);
}

///several set_* method
inline void SITEXT::set_select_font(SIFONT_PC tfontpc)
{
	for (SICHARNODE_P p = select.sp; p != select.ep; p = p->nextp)
		p->char_infop->fontpc = tfontpc;
	select.ep->char_infop->fontpc = tfontpc;
}
inline void SITEXT::set_select_font(const SIFONT& tfont)
{
	for (SICHARNODE_P p = select.sp; p != select.ep; p = p->nextp)
		p->char_infop->fontpc = &tfont;
	select.ep->char_infop->fontpc = &tfont;
}
inline void SITEXT::set_curfont(SIFONT_PC tcurfontpc)
{
	curfontpc = tcurfontpc;
}
inline void SITEXT::set_curfont(const SIFONT& tcurfont)
{
	curfontpc = &tcurfont;
}
inline void SITEXT::set_select_color(COLORERF tcolor)
{
	for (SICHARNODE_P p = select.sp; p != select.ep; p = p->nextp)
		p->char_infop->color = tcolor;
	select.ep->char_infop->color = tcolor;
}
inline void SITEXT::set_select_lspace(LINESPACE tlspace)
{
	for (SICHARNODE_P p = select.sp; p != select.ep; p = p->nextp)
		p->char_infop->lspace = tlspace;
	select.ep->char_infop->lspace = tlspace;
}
inline void SITEXT::set_select_cspace(CHARSPACE tcspace)
{
	for (SICHARNODE_P p = select.sp; p != select.ep; p = p->nextp)
		p->char_infop->cspace = tcspace;
	select.ep->char_infop->cspace = tcspace;
}
inline void SITEXT::set_pagewidth(PAGEWIDTH tpagewidth)
{
	pagewidth = tpagewidth;
}

///several get_* method
inline bool point_on_line(SILINE L, const SIPOINT& P)
{
	return L.sp->draw_infop->POS.y <= P.y &&
		P.y < L.sp->draw_infop->POS.y + L.sp->draw_infop->L.height;
}
inline bool point_on_char_col(SICHARNODE_P np, const SIPOINT& P)
{
	return np->draw_infop->POS.x <= P.x&&
		P.x < np->draw_infop->POS.x + np->draw_infop->L.width;
}
inline SICURSORP SITEXT::point_to_cursorp(const SIPOINT& P)
{
	SICURSORP p;
	std::vector<SILINE>::iterator it;
	for (it = vlinep.begin(); it != vlinep.end(); ++it)
		if (point_on_line(*it, P)) break;
	if (it == vlinep.end()) return tailp;
	for (p = it->sp; p != it->ep; p = p->nextp)
		if (point_on_char_col(p, P)) break;
	if (p == it->ep) p = p->prevp;
	return p;
}

inline void SITEXT::repaint()
{
	pre_proc();
	proc_text();
}


/*
//Draw method
///cursor - coord transparent
///divide line
///line texing
inline void SITEXT::repaint()
{

}
*/
//#include<ctime>
/*
int main()
{
//	srand(time(0));
//	printf("%d", rand() % 4);
SITEXT* textp;
textp = new SITEXT;
textp->ins_char('a',10,5);
textp->cursorp->prevp->char_infop->set_cspace(50);
textp->cursorp->prevp->char_infop->set_lspace(10);
textp->ins_char('b', 100, 7);
textp->ins_char('c',13,5);
//	textp->mov_cursorp(SITEXT::DLEFT);
textp->ins_char('d', 12, 10);
textp->ins_char('\n', 0, 0);
textp->ins_char('X', 1, 1);
textp->cursorp->prevp->char_infop->set_lspace(10);
textp->('Z', 12, 20);
textp->cursorp->prevp->char_infop->set_cspace(88);
textp->repaint();
textp->print_list();

return 0;
}
*/


#endif