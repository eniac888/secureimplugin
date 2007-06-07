// Windows API

#define STRICT
#define WIN32_LEAN_AND_MEAN

#if _MSC_VER > 1000
#include <windows.h>
#else
#include <afxwin.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#pragma comment(linker,"/filealign:16")
//#pragma comment(linker,"/align:16")
#ifdef _DEBUG
#pragma comment(lib,"crypto/Debug/cryptlib.lib")
#else
#pragma comment(lib,"crypto/Release/cryptlib.lib")
#endif
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"user32.lib")
#pragma optimize("gsy", on)

#ifndef M_API_H__
#define M_API_H__

// Miranda API
#define _STATIC
#include "newpluginapi.h"
#include "m_plugins.h"
#include "m_system.h"
#include "m_database.h"
#include "m_protomod.h"
#include "m_protosvc.h"
#include "m_utils.h"
#include "m_updater.h"

#endif

#include "cryptopp.h"
#include "version.h"
#include "resource.h"
#include "dllloader.h"
#include "mmi.h"
#include "utf8.h"
#include "base16.h"
#include "base64.h"
#include "gettime.h"

// shared vars
extern HINSTANCE g_hInst;
extern PLUGINLINK *pluginLink;
extern PLUGININFO pluginInfo;
extern PLUGININFOEX pluginInfoEx;
extern MM_INTERFACE memoryManagerInterface;
extern MUUID interfaces[];

extern char TEMP[MAX_PATH];
extern int  TEMP_SIZE;
extern BOOL isVista;

extern void ExtractFile(char*,int,int);

#define MIID_CRYPTOPP	{0x3613F2D9, 0xC040, 0x4361, { 0xA4, 0x4F, 0xDF, 0x7B, 0x5A, 0xAA, 0xCF, 0x6E }} //3613F2D9-C040-4361-A44F-DF7B5AAACF6E

#define DLLEXPORT __declspec(dllexport)

extern "C" {

 DLLEXPORT int Load(PLUGINLINK *);
 DLLEXPORT PLUGININFO *MirandaPluginInfo(DWORD);
 DLLEXPORT PLUGININFOEX *MirandaPluginInfoEx(DWORD);
 DLLEXPORT MUUID* MirandaPluginInterfaces(void);
 DLLEXPORT int Unload();

 DLLEXPORT int   __cdecl cpp_create_context(int); // create crypt-context
 DLLEXPORT void  __cdecl cpp_delete_context(int); // delete crypt-context
 DLLEXPORT void  __cdecl cpp_reset_context(int);  // reset crypt-context (free all data)
		   void  __cdecl cpp_alloc_pdata(pCNTX);
 DLLEXPORT LPSTR __cdecl cpp_init_keya(int,int);    // make KeyA
 DLLEXPORT int   __cdecl cpp_init_keyb(int,LPCSTR); // load KeyB
 DLLEXPORT int   __cdecl cpp_calc_keyx(int);        // calculate KeyX
 DLLEXPORT int   __cdecl cpp_init_keyp(int,LPCSTR); // make KeyP from password
 DLLEXPORT LPSTR __cdecl cpp_encodeA(int,LPCSTR); // encode ANSIz string
 DLLEXPORT LPSTR __cdecl cpp_encodeW(int,LPWSTR); // encode USC2z string
 DLLEXPORT LPSTR __cdecl cpp_decode(int,LPCSTR);  // decode as ANSIzUCS2z
 DLLEXPORT int   __cdecl cpp_encrypt_file(int,LPCSTR,LPCSTR); // encrypt file
 DLLEXPORT int   __cdecl cpp_decrypt_file(int,LPCSTR,LPCSTR); // decrypt file
 DLLEXPORT int   __cdecl cpp_get_features(int); // get features field from client
 DLLEXPORT int   __cdecl cpp_get_error(int);    // get last error code
 DLLEXPORT int   __cdecl cpp_get_version(void); // get dll version
 DLLEXPORT int   __cdecl cpp_size_keyx(void);
 DLLEXPORT void  __cdecl cpp_get_keyx(int,byte*); // get crypto key
 DLLEXPORT void  __cdecl cpp_set_keyx(int,byte*); // set crypto key
 DLLEXPORT int   __cdecl cpp_size_keyp(void);
 DLLEXPORT void  __cdecl cpp_get_keyp(int,byte*); // get pre-shared key
 DLLEXPORT void  __cdecl cpp_set_keyp(int,byte*); // set pre-shared key
 DLLEXPORT int   __cdecl cpp_keya(int); // KeyA exist ?
 DLLEXPORT int   __cdecl cpp_keyb(int); // KeyB exist ?
 DLLEXPORT int   __cdecl cpp_keyx(int); // KeyX exist ?
 DLLEXPORT int   __cdecl cpp_keyp(int); // KeyP exist ?

 DLLEXPORT int   __cdecl pgp_init(void);
 DLLEXPORT int   __cdecl pgp_done(void);
 DLLEXPORT int   __cdecl pgp_open_keyrings(LPSTR,LPSTR);
 DLLEXPORT int   __cdecl pgp_close_keyrings(void);
 DLLEXPORT int   __cdecl pgp_get_version(void);
 DLLEXPORT LPSTR __cdecl pgp_get_error(void);
 DLLEXPORT int   __cdecl pgp_set_key(int,LPCSTR);
 DLLEXPORT int   __cdecl pgp_set_keyid(int,PVOID);
 DLLEXPORT int   __cdecl pgp_size_keyid(void);
 DLLEXPORT PVOID __cdecl pgp_select_keyid(HWND,LPSTR);
 DLLEXPORT LPSTR __cdecl pgp_encodeA(int,LPCSTR);
 DLLEXPORT LPSTR __cdecl pgp_encodeW(int,LPCWSTR);
 DLLEXPORT LPSTR __cdecl pgp_decode(int,LPCSTR);

 DLLEXPORT int   __cdecl gpg_init(void);
 DLLEXPORT int   __cdecl gpg_done(void);
 DLLEXPORT int   __cdecl gpg_open_keyrings(LPSTR,LPSTR);
 DLLEXPORT int   __cdecl gpg_close_keyrings(void);
 DLLEXPORT void  __cdecl gpg_set_log(LPCSTR);
 DLLEXPORT LPSTR __cdecl gpg_get_error(void);
 DLLEXPORT int   __cdecl gpg_set_key(int,LPCSTR);
 DLLEXPORT int   __cdecl gpg_set_keyid(int,LPCSTR);
 DLLEXPORT int   __cdecl gpg_size_keyid(void);
 DLLEXPORT int   __cdecl gpg_select_keyid(HWND,LPSTR);
 DLLEXPORT LPSTR __cdecl gpg_encodeA(int,LPCSTR);
 DLLEXPORT LPSTR __cdecl gpg_encodeW(int,LPCWSTR);
 DLLEXPORT LPSTR __cdecl gpg_decode(int,LPCSTR);
 DLLEXPORT LPSTR __cdecl gpg_get_passphrases();
 DLLEXPORT void  __cdecl gpg_set_passphrases(LPCSTR);

 DLLEXPORT int   __cdecl rsa_init(pRSA_EXPORT*,pRSA_IMPORT);
 DLLEXPORT int   __cdecl rsa_done(void);
}