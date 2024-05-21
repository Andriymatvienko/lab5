#include "shape_editor.h"
bool startLineEdit = false; 
bool startRectEdit = false; 
bool startEllipseEdit = false; 
bool startPointEdit = false; 
long countObj = 0; 

Shape** pshape = new Shape * [115];
void ShapeObjectsEditor::StartLineEditor(HWND hwnd, UINT uint_item_menu)
{
	CheckMenuItem(GetMenu(hwnd), 32773, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32772, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32774, MF_UNCHECKED);

	startRectEdit = false; 
	startEllipseEdit = false; 
	startPointEdit = false;

	if (CheckMenuItem(GetMenu(hwnd), uint_item_menu, NULL) == MF_CHECKED){
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_UNCHECKED);
	}
	else {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_CHECKED); 
	}
	startLineEdit =! startLineEdit;
	delete shapeeditor; shapeeditor = new LineEditor();
	delete shape; shape = new LineShape(); 
}

void ShapeObjectsEditor::StartRectEditor(HWND hwnd, UINT uint_item_menu)
{
	CheckMenuItem(GetMenu(hwnd), 32773, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32771, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32774, MF_UNCHECKED);

	startLineEdit = false;
	startEllipseEdit = false;
	startPointEdit = false;

	if (CheckMenuItem(GetMenu(hwnd), uint_item_menu, NULL) == MF_CHECKED) {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_UNCHECKED);
	}
	else {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_CHECKED);
	}
	startRectEdit =! startRectEdit;
	delete shapeeditor; shapeeditor = new RectangleEditor();
	delete shape; shape = new RectangleShape();
}

void ShapeObjectsEditor::StartEllipseEditor(HWND hwnd, UINT uint_item_menu)
{
	CheckMenuItem(GetMenu(hwnd), 32772, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32771, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32774, MF_UNCHECKED);

	startLineEdit = false;
	startRectEdit = false;
	startPointEdit = false;

	if (CheckMenuItem(GetMenu(hwnd), uint_item_menu, NULL) == MF_CHECKED) {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_UNCHECKED);
	}
	else {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_CHECKED);
	}
	startEllipseEdit = !startEllipseEdit;
	delete shapeeditor; shapeeditor = new EllipseEditor();
	delete shape; shape = new EllipseShape();
}

void ShapeObjectsEditor::StartPointEditor(HWND hwnd, UINT uint_item_menu)
{
	CheckMenuItem(GetMenu(hwnd), 32773, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32771, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32772, MF_UNCHECKED);

	startLineEdit = false;
	startEllipseEdit = false;
	startRectEdit = false; 

	if (CheckMenuItem(GetMenu(hwnd), uint_item_menu, NULL) == MF_CHECKED) {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_UNCHECKED);
	}
	else {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_CHECKED);
	}
	startPointEdit = !startPointEdit;
	delete shapeeditor; shapeeditor = new PointEditor();
	delete shape; shape = new PointShape();
}

void ShapeObjectsEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
	if (startLineEdit){
		shapeeditor->OnMouseMove(hwnd, lParam); 
	}
	if (startRectEdit) {
		shapeeditor->OnMouseMove(hwnd, lParam); 
	}
	if (startEllipseEdit) {
		shapeeditor->OnMouseMove(hwnd, lParam); 
	}
	if (startPointEdit) {
		shapeeditor->OnMouseMove(hwnd, lParam); 
	}
}

void ShapeObjectsEditor::OnLBup(HWND hwnd, LPARAM lParam) {
	if (startLineEdit) {
		shapeeditor->OnLBup(hwnd, lParam); 
		shapeeditor->OnLBup(hwnd, lParam);
		long x1, y1, x2, y2;
		x1 = dynamic_cast<LineEditor*>(shapeeditor)->sPos.x;
		y1 = dynamic_cast<LineEditor*>(shapeeditor)->sPos.y; 
		x2 = dynamic_cast<LineEditor*>(shapeeditor)->ePos.x;
		y2 = dynamic_cast<LineEditor*>(shapeeditor)->ePos.y; 
		shape->Set(x1, y1, x2, y2);
		pshape[countObj] = shape;
		countObj++;
		InvalidateRect(hwnd, NULL, TRUE);
	}
	if (startRectEdit) {
		shapeeditor->OnLBup(hwnd, lParam); 
		long x1, y1, x2, y2;
		x1 = dynamic_cast<RectangleEditor*>(shapeeditor)->sPos.x; 
		y1 = dynamic_cast<RectangleEditor*>(shapeeditor)->sPos.y; 
		x2 = dynamic_cast<RectangleEditor*>(shapeeditor)->ePos.x;
		y2 = dynamic_cast<RectangleEditor*>(shapeeditor)->ePos.y; 
		shape->Set(x1, y1, x2, y2); 
		pshape[countObj] = shape;
		countObj++; 
		InvalidateRect(hwnd, NULL, TRUE); 
	}
	if (startEllipseEdit) {
		shapeeditor->OnLBup(hwnd, lParam); 
		long x1, y1, x2, y2;
		x1 = dynamic_cast<EllipseEditor*>(shapeeditor)->sPos.x;
		y1 = dynamic_cast<EllipseEditor*>(shapeeditor)->sPos.y;
		x2 = dynamic_cast<EllipseEditor*>(shapeeditor)->ePos.x;
		y2 = dynamic_cast<EllipseEditor*>(shapeeditor)->ePos.y;
		shape->Set(x1, y1, x2, y2);
		pshape[countObj] = shape;
		countObj++; 
		InvalidateRect(hwnd, NULL, TRUE);
	}
	if (startPointEdit) {
		shapeeditor->OnLBup(hwnd, lParam); 
		long x1, y1; 
		x1 = dynamic_cast<PointEditor*>(shapeeditor)->sPos.x;
		y1 = dynamic_cast<PointEditor*>(shapeeditor)->sPos.y; 
		shape->Set(x1, y1, 0, 0); 
		pshape[countObj] = shape;
		countObj++; 
		InvalidateRect(hwnd, NULL, TRUE);
	}
}

void ShapeObjectsEditor::OnLBDown(HWND hwnd, LPARAM lParam) {
	if (startLineEdit) {
		shapeeditor->OnLBdown(hwnd, lParam); 
	}
	if (startRectEdit) {
		shapeeditor->OnLBdown(hwnd, lParam); 
	}
	if (startEllipseEdit) {
		shapeeditor->OnLBdown(hwnd, lParam); 
	}
	if (startPointEdit) {
		shapeeditor->OnLBdown(hwnd, lParam); 
	}
}

void ShapeObjectsEditor::OnPaint(HWND hwnd) {
	HDC hdc = GetDC(hwnd);
	if (countObj < 115)
	{
		for (std::uint32_t i = 0; i < countObj; i++)
		{
			if (pshape[i] != nullptr)
			{
				pshape[i]->Show(hdc);
				pshape[i] = nullptr;
			}
		}
	}
	else
	{
		MessageBox(hwnd, L"Objects limit!", MB_OK, NULL); 
	}
	ReleaseDC(hwnd, hdc);
}

ShapeObjectsEditor::ShapeObjectsEditor() {
	shapeeditor = nullptr; 
	shape = nullptr; 
}; 
ShapeObjectsEditor::~ShapeObjectsEditor() {
	delete shape; 
	delete shapeeditor; 
	delete[] pshape;
}