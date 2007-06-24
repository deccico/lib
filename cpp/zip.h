#ifndef _zip_H
#define _zip_H


// ZIP functions -- for creating zip files
// This file is a repackaged form of the Info-Zip source code available
// at www.info-zip.org. The original copyright notice may be found in
// zip.cpp. The repackaging was done by Lucian Wischik to simplify its
// use in Windows/C++.


#ifndef _unzip_H
DECLARE_HANDLE(HZIP);
#endif
// An HZIP identifies a zip file that is being created

typedef DWORD ZRESULT;
// return codes from any of the zip functions. Listed later.


#define ZIP_HANDLE   1
#define ZIP_FILENAME 2
#define ZIP_MEMORY   3
#define ZIP_FOLDER   4


HZIP CreateZip(void *z,unsigned int len,DWORD flags);
// CreateZip - call this to start the creation of a zip file.
// As the zip is being created, it will be stored somewhere:
// to a pipe:              CreateZip(hpipe_write, 0,ZIP_HANDLE);
// in a file (by handle):  CreateZip(hfile, 0,ZIP_HANDLE);
// in a file (by name):    CreateZip("c:\\test.zip", 0,ZIP_FILENAME);
// in memory:              CreateZip(buf, len,ZIP_MEMORY);
// or in pagefile memory:  CreateZip(0, len,ZIP_MEMORY);
// The final case stores it in memory backed by the system paging file,
// where the zip may not exceed len bytes. This is a bit friendlier than
// allocating memory with new[]: it won't lead to fragmentation, and the
// memory won't be touched unless needed.
// Note: because pipes don't allow random access, the structure of a zipfile
// created into a pipe is slightly different from that created into a file
// or memory. In particular, the compressed-size of the item cannot be
// stored in the zipfile until after the item itself. (Also, for an item added
// itself via a pipe, the uncompressed-size might not either be known until
// after.) This is not normally a problem. But if you try to unzip via a pipe
// as well, then the unzipper will not know these things about the item until
// after it has been unzipped. Therefore: for unzippers which don't just write
// each item to disk or to a pipe, but instead pre-allocate memory space into
// which to unzip them, then either you have to create the zip not to a pipe,
// or you have to add items not from a pipe, or at least when adding items
// from a pipe you have to specify the length.


ZRESULT ZipAdd(HZIP hz,const char *dstzn, void *src,unsigned int len, DWORD flags);
// ZipAdd - call this for each file to be added to the zip.
// dstzn is the name that the file will be stored as in the zip file.
// The file to be added to the zip can come
// from a pipe:  ZipAdd(hz,"file.dat", hpipe_read,0,ZIP_HANDLE);
// from a file:  ZipAdd(hz,"file.dat", hfile,0,ZIP_HANDLE);
// from a fname: ZipAdd(hz,"file.dat", "c:\\docs\\origfile.dat",0,ZIP_FILENAME);
// from memory:  ZipAdd(hz,"subdir\\file.dat", buf,len,ZIP_MEMORY);
// (folder):     ZipAdd(hz,"subdir",   0,0,ZIP_FOLDER);
// Note: if adding an item from a pipe, and if also creating the zip file itself
// to a pipe, then you might wish to pass a non-zero length to the ZipAdd
// function. This will let the zipfile store the items size ahead of the
// compressed item itself, which in turn makes it easier when unzipping the
// zipfile into a pipe.

ZRESULT ZipGetMemory(HZIP hz, void **buf, unsigned long *len);
// ZipGetMemory - If the zip was created in memory, via ZipCreate(0,ZIP_MEMORY),
// then this function will return information about that memory block.
// buf will receive a pointer to its start, and len its length.
// Note: you can't add any more after calling this.

ZRESULT CloseZip(HZIP hz);
// CloseZip - the zip handle must be closed with this function.

unsigned int FormatZipMessage(ZRESULT code, char *buf,unsigned int len);
// FormatZipMessage - given an error code, formats it as a string.
// It returns the length of the error message. If buf/len points
// to a real buffer, then it also writes as much as possible into there.



// These are the result codes:
#define ZR_OK         0x00000000     // nb. the pseudo-code zr-recent is never returned,
#define ZR_RECENT     0x00000001     // but can be passed to FormatZipMessage.
// The following come from general system stuff (e.g. files not openable)
#define ZR_GENMASK    0x0000FF00
#define ZR_NODUPH     0x00000100     // couldn't duplicate the handle
#define ZR_NOFILE     0x00000200     // couldn't create/open the file
#define ZR_NOALLOC    0x00000300     // failed to allocate some resource
#define ZR_WRITE      0x00000400     // a general error writing to the file
#define ZR_NOTFOUND   0x00000500     // couldn't find that file in the zip
#define ZR_MORE       0x00000600     // there's still more data to be unzipped
#define ZR_CORRUPT    0x00000700     // the zipfile is corrupt or not a zipfile
#define ZR_READ       0x00000800     // a general error reading the file
// The following come from mistakes on the part of the caller
#define ZR_CALLERMASK 0x00FF0000
#define ZR_ARGS       0x00010000     // general mistake with the arguments
#define ZR_NOTMMAP    0x00020000     // tried to ZipGetMemory, but that only works on mmap zipfiles, which yours wasn't
#define ZR_MEMSIZE    0x00030000     // the memory size is too small
#define ZR_FAILED     0x00040000     // the thing was already failed when you called this function
#define ZR_ENDED      0x00050000     // the zip creation has already been closed
#define ZR_MISSIZE    0x00060000     // the indicated input file size turned out mistaken
#define ZR_PARTIALUNZ 0x00070000     // the file had already been partially unzipped
#define ZR_ZMODE      0x00080000     // tried to mix creating/opening a zip 
// The following come from bugs within the zip library itself
#define ZR_BUGMASK    0xFF000000
#define ZR_NOTINITED  0x01000000     // initialisation didn't work
#define ZR_SEEK       0x02000000     // trying to seek in an unseekable file
#define ZR_NOCHANGE   0x04000000     // changed its mind on storage, but not allowed
#define ZR_FLATE      0x05000000     // an internal error in the de/inflation code






// e.g.
//
// (1) Traditional use, creating a zipfile from existing files
//     HZIP hz = CreateZip("c:\\temp.zip",0,ZIP_FILENAME);
//     ZipAdd(hz,"src1.txt",  "c:\\src1.txt",0,ZIP_FILENAME);
//     ZipAdd(hz,"src2.bmp",  "c:\\src2_origfn.bmp",0,ZIP_FILENAME);
//     CloseZip(hz);
//
// (2) Memory use, creating an auto-allocated mem-based zip file from various sources
//     HZIP hz = CreateZip(0,100000,ZIP_MEMORY);
//     // adding a conventional file...
//     ZipAdd(hz,"src1.txt",  "c:\\src1.txt",0,ZIP_FILENAME);
//     // adding something from memory...
//     char buf[1000]; for (int i=0; i<1000; i++) buf[i]=(char)(i&0x7F);
//     ZipAdd(hz,"file.dat",  buf,1000,ZIP_MEMORY);
//     // adding something from a pipe...
//     HANDLE hread,hwrite; CreatePipe(&hread,&write,NULL,0);
//     HANDLE hthread = CreateThread(ThreadFunc,(void*)hwrite);
//     ZipAdd(hz,"unz3.dat",  hread,0,ZIP_HANDLE);
//     WaitForSingleObject(hthread,INFINITE);
//     CloseHandle(hthread); CloseHandle(hread);
//     ... meanwhile DWORD CALLBACK ThreadFunc(void *dat)
//                   { HANDLE hwrite = (HANDLE)dat;
//                     char buf[1000]={17};
//                     DWORD writ; WriteFile(hwrite,buf,1000,&writ,NULL);
//                     CloseHandle(hwrite);
//                     return 0;
//                   }
//     // and now that the zip is created, let's do something with it:
//     void *zbuf; unsigned long zlen; ZipGetMemory(hz,&zbuf,&zlen);
//     HANDLE hfz = CreateFile("test2.zip",GENERIC_WRITE,CREATE_ALWAYS);
//     DWORD writ; WriteFile(hfz,zbuf,zlen,&writ,NULL);
//     CloseHandle(hfz);
//     CloseZip(hz);
//
// (3) Handle use, for file handles and pipes
//     HANDLE hzread,hzwrite; CreatePipe(&hzread,&hzwrite);
//     HANDLE hthread = CreateThread(ZipReceiverThread,(void*)hread);
//     HZIP hz = ZipCreate(hzwrite,ZIP_HANDLE);
//     // ... add to it
//     CloseZip(hz);
//     CloseHandle(hzwrite);
//     WaitForSingleObject(hthread,INFINITE);
//     CloseHandle(hthread);
//     ... meanwhile DWORD CALLBACK ThreadFunc(void *dat)
//                   { HANDLE hread = (HANDLE)dat;
//                     char buf[1000];
//                     while (true)
//                     { DWORD red; ReadFile(hread,buf,1000,&red,NULL);
//                       // ... and do something with this zip data we're receiving
//                       if (red==0) break;
//                     }
//                     CloseHandle(hread);
//                     return 0;
//                   }
//


// Now we indulge in a little skullduggery so that the code works whether
// the user has included just zip or both zip and unzip.
// Idea: if header files for both zip and unzip are present, then presumably
// the cpp files for zip and unzip are both present, so we will call
// one or the other of them based on a dynamic choice. If the header file
// for only one is present, then we will bind to that particular one.
HZIP CreateZipZ(void *z,unsigned int len,DWORD flags);
ZRESULT CloseZipZ(HZIP hz);
unsigned int FormatZipMessageZ(ZRESULT code, char *buf,unsigned int len);
bool IsZipHandleZ(HZIP hz);
#define CreateZip CreateZipZ
#ifdef _unzip_H
#undef CloseZip
#define CloseZip(hz) (IsZipHandleZ(hz)?CloseZipZ(hz):CloseZipU(hz))
#else
#define CloseZip CloseZipZ
#define FormatZipMessage FormatZipMessageZ
#endif



#endif
