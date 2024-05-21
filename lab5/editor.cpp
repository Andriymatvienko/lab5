#include "editor.h" 
long rectSavePos[4]; 
bool drawLine = false;
bool drawRect = false;
bool drawEllipse = false;
bool drawPoint = false;
void LineEditor::OnLBup(HWND hwnd, LPARAM lParam){
    drawLine = false; 
    OnPaint(hwnd); 
}
void LineEditor::OnPaint(HWND hwnd){
    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    SetROP2(hdc, R2_NOTXORPEN);

    MoveToEx(hdc, sPos.x, sPos.y, NULL);
    LineTo(hdc, ePos.x, ePos.y); 

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}
void LineEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawLine) {
        OnPaint(hwnd);
        sPos.x = LOWORD(lParam);
        sPos.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}
void LineEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    drawLine = true;
    sPos.x = LOWORD(lParam);
    sPos.y = HIWORD(lParam);
    ePos = sPos; 
}

void RectangleEditor::OnPaint(HWND hwnd)
{
    int c_X = (sPos.x + ePos.x) / 2;
    int c_Y = (sPos.y + ePos.y) / 2;
    int wh = abs(sPos.x - ePos.x);
    int ht = abs(sPos.y - ePos.y);
    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    SetROP2(hdc, R2_NOTXORPEN);
    if (ePos.x < sPos.x)
    {
        if (ePos.y < sPos.y)
        {
            rectSavePos[0] = c_X; 
            rectSavePos[1] = c_Y; 
            rectSavePos[2] = c_X - wh; 
            rectSavePos[3] = c_Y - ht; 
            Rectangle(hdc, c_X, c_Y, c_X - wh, c_Y - ht);
        }
        else
        {
            rectSavePos[0] = c_X;
            rectSavePos[1] = c_Y;
            rectSavePos[2] = c_X - wh;
            rectSavePos[3] = c_Y + ht;
            Rectangle(hdc, c_X, c_Y, c_X - wh, c_Y + ht);
        }
    }
    else
    {
        if (ePos.y < sPos.y)
        {
            rectSavePos[0] = c_X;
            rectSavePos[1] = c_Y;
            rectSavePos[2] = c_X + wh;
            rectSavePos[3] = c_Y - ht;
            Rectangle(hdc, c_X, c_Y, c_X + wh, c_Y - ht);
        }
        else
        {
            rectSavePos[0] = c_X;
            rectSavePos[1] = c_Y;
            rectSavePos[2] = c_X + wh;
            rectSavePos[3] = c_Y + ht;
            Rectangle(hdc, c_X, c_Y, c_X + wh, c_Y + ht);
        }
    }

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}

void RectangleEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    drawRect = true;
    sPos.x = LOWORD(lParam); 
    sPos.y = HIWORD(lParam);
    ePos = sPos;
}

void RectangleEditor::OnLBup(HWND hwnd, LPARAM lParam)
{
    drawRect = false; 
    OnPaint(hwnd); 
    sPos.x = rectSavePos[0]; 
    sPos.y = rectSavePos[1]; 
    ePos.x = rectSavePos[2]; 
    ePos.y = rectSavePos[3]; 

}

void RectangleEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawRect){
        OnPaint(hwnd);
        ePos.x = LOWORD(lParam);
        ePos.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}

void EllipseEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    drawEllipse = true; 
    sPos.x = LOWORD(lParam);
    sPos.y = HIWORD(lParam);
    ePos = sPos; 
}

void EllipseEditor::OnLBup(HWND hwnd, LPARAM lParam)
{
    drawEllipse = false; 
    OnPaint(hwnd); 
} 

void EllipseEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawEllipse)
    {
        OnPaint(hwnd);
        ePos.x = LOWORD(lParam);
        ePos.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}

void EllipseEditor::OnPaint(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPen);

    SetROP2(hdc, R2_NOTXORPEN);

    Ellipse(hdc, sPos.x, sPos.y, ePos.x, ePos.y);

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}

void PointEditor::OnLBup(HWND hwnd, LPARAM lParam) {
    drawPoint = false;
    OnPaint(hwnd);
}

void PointEditor::OnPaint(HWND hwnd) {

}

void PointEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawPoint) {
        OnPaint(hwnd);
        sPos.x = LOWORD(lParam);
        sPos.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}

void PointEditor::OnLBdown(HWND hwnd, LPARAM lParam){
    drawPoint = true;
    sPos.x = LOWORD(lParam);
    sPos.y = HIWORD(lParam);
}

void ShapeEditor::OnLBdown(HWND, LPARAM) {};
void ShapeEditor::OnLBup(HWND, LPARAM) {};
void ShapeEditor::OnMouseMove(HWND, LPARAM) {};
void ShapeEditor::OnPaint(HWND) {};