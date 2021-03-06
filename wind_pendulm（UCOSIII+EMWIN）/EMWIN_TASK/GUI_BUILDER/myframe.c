/******************
***************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.30                          *
*        Compiled Jul  1 2015, 10:50:32                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "myframe.h"
#include "angletask.h"
#include "motor_control.h"
#include "myiconview.h"
#include "bmpdisplay.h"
#include "EmWinHZFont.h"
#include "ff.h"
#include "xbffontcreate.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0  (GUI_ID_USER + 0x00)
#define ID_DROPDOWN_0  (GUI_ID_USER + 0x01)
#define ID_BUTTON_0  (GUI_ID_USER + 0x02)
#define ID_BUTTON_1  (GUI_ID_USER + 0x03)
#define ID_TEXT_0  (GUI_ID_USER + 0x06)
#define ID_TEXT_1  (GUI_ID_USER + 0x08)
#define ID_TEXT_3   (GUI_ID_USER + 0x11) 
#define ID_TEXT_4   (GUI_ID_USER + 0x12) 
#define ID_BUTTON_2  (GUI_ID_USER + 0x09)
#define ID_BUTTON_3  (GUI_ID_USER + 0x0A)
#define ID_TEXT_2  (GUI_ID_USER + 0x0B)
#define ID_TEXT_5   (GUI_ID_USER + 0x13) 
#define ID_DROPDOWN_1  (GUI_ID_USER + 0x0F)



// USER START (Optionally insert additional defines)
#define ID_ICONVIEW_0  (GUI_ID_USER + 0x10)    //显示图片

#define ID_IMAGE_0_IMAGE_0   0x00

// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

extern GUI_CONST_STORAGE GUI_BITMAP bmBlack;
extern GUI_CONST_STORAGE GUI_BITMAP bmWhite;
extern GUI_CONST_STORAGE GUI_BITMAP bmangleblack;
extern GUI_CONST_STORAGE GUI_BITMAP bmanglewhite;


/*********************************************************************
*
*       _acImage_0, "C:\Users\yexiaobai\Desktop\mytest.bmp", ID_IMAGE_0_IMAGE_0
*/



// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
   {WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 480, 273, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0, 11, 15, 73, 18, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 219, 113, 87, 27, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 328, 113, 87, 27, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 59,118, 70, 30, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_3, 129,118, 70, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 53, 158, 70, 30, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_4, 123,158, 70, 30, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 222, 156, 87, 27, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 332, 155, 87, 27, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 60, 207, 80, 30, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_5, 10, 234, 400, 40, 0, 0x64, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_1, 214, 205, 158, 23, 0, 0x0, 0 },
  { ICONVIEW_CreateIndirect, "Iconview", ID_ICONVIEW_0, 100, 0, 340, 120, WM_CF_HASTRANS|WM_CF_SHOW, (100<<16)|100,0 },
  // USER START (Optionally insert additional widgets)
	
	// USER END  WM_CF_HASTRANS|WM_CF_SHOW
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
static const BITMAP_ITEM BitmapItem[]={
	{&bmCamera,    "Camera"},
	{&bmFolder,    "Folder"},
	{&bmHome,      "Home"},
	
};





// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
	int     value;
	u8    buf[30];
	const void * pdata;
	u16  i;
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
   hItem = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_0);
  ICONVIEW_SetFont(hItem,&GUI_Font16_ASCII);
	ICONVIEW_SetBkColor(hItem,ICONVIEW_CI_SEL,GUI_WHITE|0X70000000);
	ICONVIEW_SetSpace(hItem,GUI_COORD_X,15);
	ICONVIEW_SetSpace(hItem,GUI_COORD_Y,15);
	ICONVIEW_SetIconAlign(hItem,ICONVIEW_IA_HCENTER|ICONVIEW_IA_VCENTER);
	for(i=0;i<(GUI_COUNTOF(BitmapItem));i++)
	{
		ICONVIEW_AddBitmapItem(hItem,BitmapItem[i].pBitmap,BitmapItem[i].pText);
	}  
	
	
	
	// Initialization of 'Dropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
		DROPDOWN_SetAutoScroll(hItem,1);	//启用自动使用滚动条
    DROPDOWN_AddString(hItem, "Mode1");
    DROPDOWN_SetFont(hItem, GUI_FONT_13B_ASCII);
    DROPDOWN_AddString(hItem, "Mode2");
    DROPDOWN_AddString(hItem, "Mode3");
    DROPDOWN_AddString(hItem, "Mode4");
    DROPDOWN_AddString(hItem, "Mode5");
    DROPDOWN_SetListHeight(hItem, 54);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetBitmapEx(hItem,0,&bmBlack,-1,0);
		BUTTON_SetText(hItem, "");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetBitmapEx(hItem,0,&bmWhite,-1,0);
		BUTTON_SetText(hItem, "");
    //
    // Initialization of 'Text0'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetText(hItem, "半径: ");
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00400080));
		TEXT_SetFont(hItem, &XBF12_Font);
    //
		 // Initialization of 'Text3'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		TEXT_SetText(hItem, "15.0cm");
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00400080));
		TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'Text1'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "角度 : ");
    TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x000080FF));
    TEXT_SetFont(hItem,  &XBF12_Font);
    //
		// Initialization of 'Text4'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "0.0°");
    TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x000080FF));
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
		// Initialization of 'Text5'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetText(hItem,"湖南大学风力摆控制系统--By香蕉君");
    TEXT_SetTextColor(hItem, GUI_WHITE);
    TEXT_SetFont(hItem, &XBF12_Font);
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetBitmapEx(hItem,0,&bmangleblack,0,0);
		BUTTON_SetText(hItem, "");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetBitmapEx(hItem,0,&bmanglewhite,0,0);
		BUTTON_SetText(hItem,"");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem,"旋转方向:");
    TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00800040));
    TEXT_SetFont(hItem,  &XBF12_Font);
    //
    // Initialization of 'Dropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_1);
		DROPDOWN_SetAutoScroll(hItem,1);	//启用自动使用滚动条
    DROPDOWN_SetListHeight(hItem, 50);
    DROPDOWN_AddString(hItem,"顺时针");
    DROPDOWN_SetFont(hItem,  &XBF12_Font);
    DROPDOWN_AddString(hItem,"逆时针");
    // USER START (Optionally insert additional code for further widget initialization)
//    hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
//		pdata = _GetImageById(ID_IMAGE_0_IMAGE_0, &FileSize);
//		IMAGE_SetBMP(hItem,pdata,FileSize);
		
	
		// USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_DROPDOWN_0: // Notifications sent by 'Dropdown'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
         hItem = WM_GetDialogItem(pMsg->hWin,ID_DROPDOWN_0);
			   value=DROPDOWN_GetSel(hItem);
			   switch(value)
				 {
				   case 0: Mode = 1;break;
					 case 1: Mode = 2;break;
					 case 2: Mode = 3;break;
					 case 3: Mode = 4;break;
					 case 4: Mode = 5;break;
					 default:break;			 
				 }
			   
			
			  // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        if(Radius<35.0f)
			   Radius = Radius + 5.0f;
				sprintf((char*)buf,"%.1fcm",Radius);
				hItem = WM_GetDialogItem(pMsg->hWin,ID_TEXT_3);
				TEXT_SetText(hItem, (char*)buf);
				TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
				TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
				TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00400080));	
			  // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
			 if(Radius>15.0f)
			  Radius = Radius - 5.0f;
				sprintf((char*)buf,"%.1fcm",Radius);
				hItem = WM_GetDialogItem(pMsg->hWin,ID_TEXT_3);
				TEXT_SetText(hItem, (char*)buf);
				TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
				TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
				TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00400080));	        
			
			  // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
		  
			// USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
			 if(Angle<360.0f)
			  Angle = Angle + 10.0f;
				sprintf((char*)buf,"%.1f",Angle);
				hItem = WM_GetDialogItem(pMsg->hWin,ID_TEXT_4);
				TEXT_SetText(hItem, (char*)buf);
				TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
				TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
				TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x000080FF));         
			
					
			 // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        
			 if(Angle>0.0f)
			  Angle = Angle - 10.0f;
				sprintf((char*)buf,"%.1f",Angle);
				hItem = WM_GetDialogItem(pMsg->hWin,ID_TEXT_4);
				TEXT_SetText(hItem, (char*)buf);
				TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
				TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
				TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x000080FF));
			
			  // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_DROPDOWN_1: // Notifications sent by 'Dropdown'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        hItem = WM_GetDialogItem(pMsg->hWin,ID_DROPDOWN_1);
			  value =  DROPDOWN_GetSel(hItem);
			  switch(value)
				{
				  case 0: RoundDir = 1; break;
					case 1: RoundDir = 0; break;
					default:break;
								
				}
			   
			  // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
	case WM_PAINT:
		//GUI_DrawBitmap(&bmbackground,0,0);
		changebackgroudbmp();
	// USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
