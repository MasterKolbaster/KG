#include "NewGraphics.h"

void NewGraphics::OnUserCreate()
{
	shapes.resize(2);

	shapes[0].tris =
	{
		// ����� �������
		{ 0.0f, 0.0f, 0.0f,    0.0f, 2.0f, 0.0f,    1.0f, 2.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 2.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// ���������                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 2.0f, 0.0f,    1.0f, 2.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 2.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// ��������                                                     
		{ 0.0f, 0.0f, 0.0f,    0.0f, 2.0f, 0.0f,    1.0f, 2.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 1.0f,    1.0f, 2.0f, 1.0f },

		// ����                                                      
		{ 0.0f, 2.0f, 0.0f,    1.0f, 2.0f, 1.0f,    1.0f, 2.0f, 0.0f },

		//���                                                  
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
	};

	shapes[1].tris =
	{
		// ����� �������
		{ 0.0f, 0.0f, 0.0f,    0.0f, 2.0f, 0.0f,    1.0f, 2.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 2.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// ���������                                                     
		{ 1.0f, 0.0f, 0.0f,    1.0f, 2.0f, 0.0f,    1.0f, 2.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 2.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// ��������                                                      
		{ 0.0f, 0.0f, 0.0f,    0.0f, 2.0f, 0.0f,    1.0f, 2.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 1.0f,    1.0f, 2.0f, 1.0f },

		// ����                                                      
		{ 0.0f, 2.0f, 0.0f,    1.0f, 2.0f, 1.0f,    1.0f, 2.0f, 0.0f },

		// ���                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
	};

	matProj = Matrix_MakeProjection(90.0f, static_cast<float>(GetConsoleHeight()) / static_cast<float>(GetConsoleWidth()), 0.1f, 1000.0f);

	lightINF.x = 1.0f;
	lightINF.y = -100.0f;
	lightINF.z = 1.0f;

	scale = 1.0f;
	_x = 1.85f, _y = 2.4f;
	fThetaX = fThetaY = fThetaZ = 0.0f;
}

void NewGraphics::OnUserUpdate(float fElapsedTime)
{
	// ������� �������, ��������� ����
	Fill(0, 0, GetConsoleWidth(), GetConsoleHeight(), PIXEL_SOLID, BG_CYAN);

	// �����
	Fill(0, iConsoleHeight / 2, iConsoleWidth, iConsoleHeight, PIXEL_SOLID, FG_GREY);

	// ��������
	if (GetKey(L'W').bHeld)					//������ ��� X 
		fThetaX += 8.0f * fElapsedTime;
	if (GetKey(L'S').bHeld)					//������ ��� X (� ������ �������) 
		fThetaX -= 8.0f * fElapsedTime;
	if (GetKey(L'A').bHeld)					//������ ��� Z 
		fThetaZ += 8.0f * fElapsedTime;
	if (GetKey(L'D').bHeld)					//������ ��� Z (� ������ �������) 
		fThetaZ -= 8.0f * fElapsedTime;
	if (GetKey(L'Q').bHeld)					//������ ��� Y 
		fThetaY += 8.0f * fElapsedTime;
	if (GetKey(L'E').bHeld)					//������ ��� Y (� ������ �������) 
		fThetaY -= 8.0f * fElapsedTime;
	if (GetKey(L'B').bHeld)
		exit(1);

	// ������������
	if (GetKey(L'Z').bHeld)		// ����������
		scale = (scale <= 1.5f) ? scale + 0.01f : scale;
	if (GetKey(L'X').bHeld)		// ����������
		scale = (scale >= 0.5f) ? scale - 0.01f : scale;

	// �����������
	if ((GetKey(L'R').bHeld)&&(_x < 2.0f))		// ������
		_x += 0.02f;
	if (GetKey(L'F').bHeld)		// �����
		_x -= 0.02f;
	if (GetKey(L'T').bHeld)		// �����
		_y -= 0.02f;
	if ((GetKey(L'G').bHeld) && (_y < 5.0f))		// ����
		_y += 0.02f;

	if (GetKey(L'L').bHeld)			//�������� ����� �����
		lightINF.x += 1.0f;

	if (GetKey(L'O').bHeld)			//�������� ����� ������
		lightINF.x -= 1.0f;

	mat4x4 matRotX, matRotY, matRotZ;
	matRotX = Matrix_MakeRotationX(fThetaX * 0.5f);
	matRotY = Matrix_MakeRotationY(fThetaY * 0.5f);
	matRotZ = Matrix_MakeRotationZ(fThetaZ * 0.5f);

	mat4x4 ScalingMatrix;
	ScalingMatrix = Matrix_MakeScale(scale, scale, scale);

	mat4x4 TranslationMatrix;
	TranslationMatrix = Matrix_MakeTranslation(0.0f, 0.0f, 0.5f);

	mat4x4 WorldMatrix;
	WorldMatrix = Matrix_MakeIdentity();
	WorldMatrix = matRotY * matRotX * matRotZ * ScalingMatrix * TranslationMatrix;

	std::vector<triangle> vecTrianglesToRaster;

	float  t = 0.0f;					
	int16_t tri_color = FG_DARK_BLUE;
	int16_t count_tris = 0;
	
		for (auto& sh : shapes)
		{
			// ��� ���� �������������
			for (auto tri : sh.tris)
			{
				triangle triProjected, triTransformed;

				triTransformed.points[0] = MultiplyMatrixVector(WorldMatrix, tri.points[0]);
				triTransformed.points[1] = MultiplyMatrixVector(WorldMatrix, tri.points[1]);
				triTransformed.points[2] = MultiplyMatrixVector(WorldMatrix, tri.points[2]);

				// 3D --> 2D
				triProjected.points[0] = MultiplyMatrixVector(matProj, triTransformed.points[0]);
				triProjected.points[1] = MultiplyMatrixVector(matProj, triTransformed.points[1]);
				triProjected.points[2] = MultiplyMatrixVector(matProj, triTransformed.points[2]);

				
				for (int16_t i = 0; i < 3; i++)
				{
					triProjected.points[i].x += _x + t;
					triProjected.points[i].y += _y;

					triProjected.points[i].x *= 0.1f * static_cast<float>(GetConsoleWidth());
					triProjected.points[i].y *= 0.1f * static_cast<float>(GetConsoleHeight());

					// ���������� ����������
					barycenter += triProjected.points[i];
				}
				count_tris++;

				// ����
				tri_color = (tri_color == FG_DARK_BLUE) ? FG_GREEN : FG_DARK_BLUE;
				triProjected.col = tri_color;

				vecTrianglesToRaster.push_back(triProjected);
			}

			
			barycenter /= count_tris * 3;

			// ���������� �������������
			std::sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](triangle& t1, triangle& t2)
				{
					float z1 = (t1.points[0].z + t1.points[1].z + t1.points[2].z) / 3.0f;
					float z2 = (t2.points[0].z + t2.points[1].z + t2.points[2].z) / 3.0f;
					return z1 > z2;
				});

			// ��������
			for (auto& tri : vecTrianglesToRaster)
			{
				for (int16_t i = 0; i < 3; i++)
				{
					tri.points[i].x = roundf(tri.points[i].x);
					tri.points[i].y = roundf(tri.points[i].y);
				}
			}

			// ������
			DrawShadowInf(vecTrianglesToRaster, lightINF);

			std::vector<triangle> vecVisibleSurfaces;
			fPoint3D view_point = { static_cast<float>(iConsoleWidth) / 2.0f, static_cast<float>(iConsoleHeight) / 2.0f, -100.0f };

			vecVisibleSurfaces = RobertsAlgorithm(vecTrianglesToRaster, view_point, barycenter, PIXEL_SOLID, FG_DARK_YELLOW, FG_DARK_RED);

			t += 5.5f;
			barycenter = 0.0f;
			count_tris = 0;
			vecTrianglesToRaster.clear();
		}
		
}
