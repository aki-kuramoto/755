package main

import (
	"syscall"
	"os"
	
	"golang.org/x/sys/windows"
)

var (
	// Shared library
	libUser32           *windows.LazyDLL
	
	wapiEnumWindows     *windows.LazyProc
	wapiSetWindowPos    *windows.LazyProc
)

func init() {
	// Library
	libUser32 = windows.NewLazySystemDLL("user32.dll")
	
	// Functions
	wapiEnumWindows     = libUser32.NewProc("EnumWindows")
	wapiSetWindowPos    = libUser32.NewProc("SetWindowPos")
}

// EnumWindows - BOOL EnumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam);
func EnumWindows(lpEnumFunc uintptr, lParam uintptr) {
	r1, r2, err := syscall.Syscall(wapiEnumWindows.Addr(), 2, uintptr(lpEnumFunc), uintptr(lParam), 0)
	// fmt.Printf("EnumWindows (%d, %d, %s)", r1, r2, err)
	_ = r1
	_ = r2
	_ = err
	
	return
}

// SetWindowPos - BOOL SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags);
func SetWindowPos(hWnd syscall.Handle, hWndInsertAfter syscall.Handle, x int32, y int32, cx int32, cy int32, uFlags uint32) bool {
	ret, _, _ := syscall.Syscall9(wapiSetWindowPos.Addr(), 7, uintptr(hWnd), uintptr(hWndInsertAfter), uintptr(x), uintptr(y), uintptr(cx), uintptr(cy), uintptr(uFlags), 0, 0)
	return ret != 0
}

func main() {
	
	cb := syscall.NewCallback(func(hWnd syscall.Handle, lParam uintptr) uintptr {
		SetWindowPos(hWnd, 0, 0, 0, 320, 320, 0);
		
		return uintptr(1)
	})
	
	EnumWindows(cb, uintptr(0))
	
	os.Exit(0)
}
