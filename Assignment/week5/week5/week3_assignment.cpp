#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT nowPoint = { 0 };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;


HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 분홍색
HBRUSH clear = CreateSolidBrush(RGB(255, 255, 255)); // 흰색
HBRUSH black = CreateSolidBrush(RGB(0, 0, 0)); // 검정색

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN: // 마우스 버튼을 놓았을 때
	{
		startPoint.x = LOWORD(lParam); // 가로 길이
		startPoint.y = HIWORD(lParam); // 세로 높이
		isMouseLButtonPressed = 1;
	}
	break;

	case WM_LBUTTONUP: // 마우스 버튼 눌렀을 때
	{
		if (isMouseLButtonPressed)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			isMouseLButtonPressed = 0;
			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_RBUTTONDOWN:
	{
		int mouseX = LOWORD(lParam);
		int mouseY = HIWORD(lParam);

		if (mouseX >= startPoint.x && mouseX <= endPoint.x && mouseY >= startPoint.y && mouseY <= endPoint.y) {
			isMouseRButtonPressed = 1;
			nowPoint.x = mouseX;
			nowPoint.y = mouseY;
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_RBUTTONUP:
	{
		isMouseRButtonPressed = 0;
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;

	case WM_MOUSEMOVE:
	{

		HDC hdc = GetDC(hwnd);

		int mouseX = LOWORD(lParam);
		int mouseY = HIWORD(lParam);

		if (isMouseRButtonPressed) {
			nowPoint.x = mouseX;
			nowPoint.y = mouseY;
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_PAINT:
	{
		HDC hdc = GetDC(hwnd);

		if (!isMouseLButtonPressed && !isMouseRButtonPressed)
		{
			RECT rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
			FrameRect(hdc, &rect, black);
			FillRect(hdc, &rect, hBrush);
			MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
		}
		else if (isMouseRButtonPressed) {
			int mouseX = nowPoint.x - endPoint.x;
			int mouseY = nowPoint.y - endPoint.y;
			startPoint.x += mouseX;
			startPoint.y += mouseY;
			endPoint.x += mouseX;
			endPoint.y += mouseY;

			RECT rect = { 0, 0, 800, 600 };
			FillRect(hdc, &rect, clear);

			rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
			FillRect(hdc, &rect, hBrush);
		}
		else
		{
			RECT rect = { 0, 0, 800, 600 };
			FillRect(hdc, &rect, clear);
		}
		ReleaseDC(hwnd, hdc);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return S_OK;
}


#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	// 윈도우 클래스 선언
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	// 예외
	}

	// Window viewport 영역 조정
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("컴소 Application"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0,
		800, 600,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임 한 쌍으로 쓴다고 보면 됨



	// 메시지 처리 루프
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리
		if (GetMessage(&msg, hwnd, 0, 0))
			// if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메시지를 쓰고 어떡할 거냐의 의미인데 지운다는 것임
		{

			// 메시지 해석해줘
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘
			DispatchMessage(&msg);

		}
	}

	//종료 메시지 보내기
	return (int)msg.wParam;
}