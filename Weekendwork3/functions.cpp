#include <iostream>
#include <string>
#include <conio.h>
#include "functions.h"

void Homework01_Run()
{
	const int FieldSize = 10;											// 가로세로 크기 지정
	int Width[FieldSize] = { 0, };										// 가로 좌표 표시용 배열
	char Height[FieldSize] = { 0, };										// 세로 좌표 표시용 배열
	std::string BattleField[FieldSize][FieldSize] = { ".", };				// 가로세로 크기만큼의 맵 (탄환 전부 소진시에는 보여줌)
	std::string HiddenField[FieldSize][FieldSize] = { ".", };				// 가로세로 크기만큼의 플레이어에게 보여주는 맵

	int ShipDeployIsVertical = 0;										// 함선 최초 배치시 세로로 배치할건지 (0은 가로배치, 1은 세로배치)
	int DeployPositionWidth = 0;										// 배치를 시도할 최초 가로좌표 (함선에 따라 배치 시도를 할 끝 위치가 다름)
	int DeployPositionHeight = 0;										// 배치를 시도할 최초 세로좌표 (함선에 따라 배치 시도를 할 끝 위치가 다름)

	int RemainShells = 30;												// 남은 공격횟수				
	std::string AttackedPosition = "?,?";								// 공격한 좌표
	std::string AttackResult = "[기본값]";								// 공격 성공 여부

	int CarrierHealth = 10;												// 항공모함 체력
	int BattleshipHealth = 10;											// 전함 체력
	int CruiserHealth = 10;												// 순양함 체력
	int DestroyerHealth = 10;											// 구축함 체력

	char InputAttackPosition[30] = {'0',};							// 공격할 좌표 입력	
	


	// 1. 맵 초기화, 함선 배치, 맵 출력 (테스트중)


	// 1_1. 맵 초기화

	for (int e = 0; e < FieldSize; e++)
	{
		Width[e] = e;
	}

	for (int e = 0; e < FieldSize; e++)
	{
		for (int f = 0; f < FieldSize; f++)
		{
			BattleField[e][f] = ".";
			HiddenField[e][f] = ".";
		}
	}
	
	// 1_2. 함선 배치

	// 순서대로 항공모함(5), 전함(4), 순양함(3), 구축함(2)

	// 1_2_1. 항공모함 ------------------------- (최초 배치이므로 중복배치 검사 안함)

	ShipDeployIsVertical = rand() % 2;

	if (ShipDeployIsVertical == 0) // 가로배치로 결정되면?
	{
		DeployPositionWidth = rand() % (FieldSize - 4); // 가로위치는 0에서 맵 끝부터 5만큼 떨어진 거리까지
		DeployPositionHeight = rand() % (FieldSize); // 세로위치는 0에서 맵 끝까지 (제한 없음)
	}
	else if (ShipDeployIsVertical == 1) // 세로배치로 결정되면?
	{
		DeployPositionWidth = rand() % (FieldSize); // 가로위치는 0에서 맵 끝까지 (제한 없음)
		DeployPositionHeight = rand() % (FieldSize - 4); // 세로위치는 0에서 맵 끝부터 5만큼 떨어진 거리까지
	}

	if (ShipDeployIsVertical == 0)
	{
		for (int e = 0; e < 5; e++)
		{
			BattleField[DeployPositionHeight][DeployPositionWidth + e] = "CV";
		}
	}
	else if (ShipDeployIsVertical == 1)
		for (int e = 0; e < 5; e++)
		{			
			BattleField[DeployPositionHeight + e][DeployPositionWidth] = "CV";
		}

	
	// 1_2_2. 전함 ------------------------- 
	
	ShipDeployIsVertical = rand() % 2;

	if (ShipDeployIsVertical == 0) // 가로배치로 결정되면?
	{
		DeployPositionWidth = rand() % (FieldSize - 3); // 가로위치는 0에서 맵 끝부터 4만큼 떨어진 거리까지
		DeployPositionHeight = rand() % (FieldSize); // 세로위치는 0에서 맵 끝까지 (제한 없음)
		while ((BattleField[DeployPositionHeight][DeployPositionWidth] != ".") || // 전함이 배치될 좌표가 하나라도 "." 이 아니면 계속 랜덤 돌리기
			(BattleField[DeployPositionHeight][DeployPositionWidth + 1] != ".") ||
			(BattleField[DeployPositionHeight][DeployPositionWidth + 2] != ".") ||
			(BattleField[DeployPositionHeight][DeployPositionWidth + 3] != "."))
		{
			DeployPositionWidth = rand() % (FieldSize - 3); // 가로위치 재설정
			DeployPositionHeight = rand() % (FieldSize); // 세로위치 재설정
		}

		// while문을 성공적으로 빠져나가면
		for (int e = 0; e < 4; e++)
		{
			BattleField[DeployPositionHeight][DeployPositionWidth + e] = "BB";
		}
	}

	if (ShipDeployIsVertical == 1) // 세로배치로 결정되면?
	{
		DeployPositionWidth = rand() % (FieldSize); // 가로위치는 0에서 맵 끝부터 4만큼 떨어진 거리까지
		DeployPositionHeight = rand() % (FieldSize - 3); // 세로위치는 0에서 맵 끝까지 (제한 없음)
		while ((BattleField[DeployPositionHeight][DeployPositionWidth] != ".") || // 전함이 배치될 좌표가 하나라도 "." 이 아니면 계속 랜덤 돌리기
			(BattleField[DeployPositionHeight + 1][DeployPositionWidth] != ".") ||
			(BattleField[DeployPositionHeight + 2][DeployPositionWidth] != ".") ||
			(BattleField[DeployPositionHeight + 3][DeployPositionWidth] != "."))
		{
			DeployPositionWidth = rand() % (FieldSize); // 가로위치 재설정
			DeployPositionHeight = rand() % (FieldSize - 3); // 세로위치 재설정
		}

		// while문을 성공적으로 빠져나가면
		for (int e = 0; e < 4; e++)
		{
			BattleField[DeployPositionHeight + e][DeployPositionWidth] = "BB";
		}
	}


	// 1_2_3. 순양함 ------------------------- 

	ShipDeployIsVertical = rand() % 2;

	if (ShipDeployIsVertical == 0) // 가로배치로 결정되면?
	{
		DeployPositionWidth = rand() % (FieldSize - 2); // 가로위치는 0에서 맵 끝부터 3만큼 떨어진 거리까지
		DeployPositionHeight = rand() % (FieldSize); // 세로위치는 0에서 맵 끝까지 (제한 없음)
		while ((BattleField[DeployPositionHeight][DeployPositionWidth] != ".") || // 순양함이 배치될 좌표가 하나라도 "." 이 아니면 계속 랜덤 돌리기
			(BattleField[DeployPositionHeight][DeployPositionWidth + 1] != ".") ||			
			(BattleField[DeployPositionHeight][DeployPositionWidth + 2] != "."))
		{
			DeployPositionWidth = rand() % (FieldSize - 2); // 가로위치 재설정
			DeployPositionHeight = rand() % (FieldSize); // 세로위치 재설정
		}

		// while문을 성공적으로 빠져나가면
		for (int e = 0; e < 3; e++)
		{
			BattleField[DeployPositionHeight][DeployPositionWidth + e] = "C";
		}
	}

	if (ShipDeployIsVertical == 1) // 세로배치로 결정되면?
	{
		DeployPositionWidth = rand() % (FieldSize); // 가로위치는 0에서 맵 끝부터 3만큼 떨어진 거리까지
		DeployPositionHeight = rand() % (FieldSize - 2); // 세로위치는 0에서 맵 끝까지 (제한 없음)
		while ((BattleField[DeployPositionHeight][DeployPositionWidth] != ".") || // 순양함이 배치될 좌표가 하나라도 "." 이 아니면 계속 랜덤 돌리기
			(BattleField[DeployPositionHeight + 1][DeployPositionWidth] != ".") ||			
			(BattleField[DeployPositionHeight + 2][DeployPositionWidth] != "."))
		{
			DeployPositionWidth = rand() % (FieldSize); // 가로위치 재설정
			DeployPositionHeight = rand() % (FieldSize - 2); // 세로위치 재설정
		}

		// while문을 성공적으로 빠져나가면
		for (int e = 0; e < 3; e++)
		{
			BattleField[DeployPositionHeight + e][DeployPositionWidth] = "C";
		}
	}


	// 1_2_4. 구축함 ------------------------- 

	ShipDeployIsVertical = rand() % 2;

	if (ShipDeployIsVertical == 0) // 가로배치로 결정되면?
	{
		DeployPositionWidth = rand() % (FieldSize - 1); // 가로위치는 0에서 맵 끝부터 2만큼 떨어진 거리까지
		DeployPositionHeight = rand() % (FieldSize); // 세로위치는 0에서 맵 끝까지 (제한 없음)
		while ((BattleField[DeployPositionHeight][DeployPositionWidth] != ".") || // 구축함이 배치될 좌표가 하나라도 "." 이 아니면 계속 랜덤 돌리기			
			(BattleField[DeployPositionHeight][DeployPositionWidth + 1] != "."))
		{
			DeployPositionWidth = rand() % (FieldSize - 1); // 가로위치 재설정
			DeployPositionHeight = rand() % (FieldSize); // 세로위치 재설정
		}

		// while문을 성공적으로 빠져나가면
		for (int e = 0; e < 2; e++)
		{
			BattleField[DeployPositionHeight][DeployPositionWidth + e] = "DD";
		}
	}

	if (ShipDeployIsVertical == 1) // 세로배치로 결정되면?
	{
		DeployPositionWidth = rand() % (FieldSize); // 가로위치는 0에서 맵 끝부터 2만큼 떨어진 거리까지
		DeployPositionHeight = rand() % (FieldSize - 1); // 세로위치는 0에서 맵 끝까지 (제한 없음)
		while ((BattleField[DeployPositionHeight][DeployPositionWidth] != ".") || // 구축함이 배치될 좌표가 하나라도 "." 이 아니면 계속 랜덤 돌리기			
			(BattleField[DeployPositionHeight + 1][DeployPositionWidth] != "."))
		{
			DeployPositionWidth = rand() % (FieldSize); // 가로위치 재설정
			DeployPositionHeight = rand() % (FieldSize - 1); // 세로위치 재설정
		}

		// while문을 성공적으로 빠져나가면
		for (int e = 0; e < 2; e++)
		{
			BattleField[DeployPositionHeight + e][DeployPositionWidth] = "DD";
		}
	}

	
	
	

	// 1_3. 맵 출력, 상태 표시

	while (((CarrierHealth > 0) || (BattleshipHealth > 0) || (CruiserHealth > 0) || (DestroyerHealth > 0)) && (RemainShells > 0))
	{
		system("cls");

		printf("--------------- [배틀쉽 게임] ---------------\n\n");

		printf(" "); // 가로좌표 패딩

		for (int e = 0; e < FieldSize; e++)
		{
			printf("%4d", Width[e]);
		}

		printf("\n\n"); // 높이 패딩

		for (int e = 0; e < FieldSize; e++)
		{
			Height[e] = 'A' + e; // ASCII code A 값에서 1만큼 증가시킴. 
			printf("%c", Height[e]);

			for (int f = 0; f < FieldSize; f++)
			{
				printf("%4s", HiddenField[e][f].c_str()); // 실제 보는 맵
			}
			printf("\n\n"); // 가로 패딩
		}
		
		// 항공모함 체력을 계산하기 (내부 데이터용)
		
		CarrierHealth = 0;

		for (int e = 0; e < FieldSize; e++)
		{
			for (int f = 0; f < FieldSize; f++)
			{
				if (BattleField[e][f] == "CV")
				{
					CarrierHealth++;
				}
			}
		}

		// 전함 체력을 계산하기 (내부 데이터용)

		BattleshipHealth = 0;

		for (int e = 0; e < FieldSize; e++)
		{
			for (int f = 0; f < FieldSize; f++)
			{
				if (BattleField[e][f] == "BB")
				{
					BattleshipHealth++;
				}
			}
		}

		// 순양함 체력을 계산하기 (내부 데이터용)

		CruiserHealth = 0;

		for (int e = 0; e < FieldSize; e++)
		{
			for (int f = 0; f < FieldSize; f++)
			{
				if (BattleField[e][f] == "C")
				{
					CruiserHealth++;
				}
			}
		}

		// 순양함 체력을 계산하기 (내부 데이터용)

		DestroyerHealth = 0;

		for (int e = 0; e < FieldSize; e++)
		{
			for (int f = 0; f < FieldSize; f++)
			{
				if (BattleField[e][f] == "DD")
				{
					DestroyerHealth++;
				}
			}
		}
		
		if ((CarrierHealth == 0 && BattleshipHealth == 0 && CruiserHealth == 0 && DestroyerHealth == 0) || RemainShells <= 0)
		{
			break;
		}
		
		
		
		
		printf("맵에는 총 4척의 함선이 있습니다. 좌표를 입력하여 공격해서 함선을 모두 제거하세요. 공격 횟수에는 제한이 있습니다.");
		printf("\n");
		if (CarrierHealth > 0) // 항공모함 생존여부에 따른 메시지 출력
		{		
			printf("[항공모함 : 생존]");
		}
		else
		{			
			printf("[항공모함 : 격파]");
		}
		
		printf(" , ");

		if (BattleshipHealth > 0) // 순양함 생존여부에 따른 메시지 출력
		{
			printf("[전함 : 생존]");
		}
		else
		{
			printf("[전함 : 격파]");
		}
		
		printf(" , ");

		if (CruiserHealth > 0) // 순양함 생존여부에 따른 메시지 출력
		{			
			printf("[순양함 : 생존]");
		}
		else
		{			
			printf("[순양함 : 격파]");
		}

		printf(" , ");

		if (DestroyerHealth > 0) // 구축함 생존여부에 따른 메시지 출력
		{
			printf("[구축함 : 생존]");
		}
		else
		{
			printf("[구축함 : 격파]");
		}

		// printf("\n항공모함의 현재 체력 : [%d]  전함의 현재 체력 : [%d]  순양함의 현재 체력 : [%d]  구축함의 현재 체력 : [%d]", CarrierHealth,BattleshipHealth,CruiserHealth,DestroyerHealth);		
		// 바로 위 출력부는 테스트용임.

		printf("\n\n공격할 좌표를 입력하세요. (예시: E3) 공격했던 좌표는 재공격할 수 없습니다.");
		printf("\n남은 공격횟수 [%d회] : ", RemainShells);

		std::cin >> InputAttackPosition;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		

		//	잘못된 좌표를 입력하거나 이미 공격한 곳을 또 지정하는 경우

		int y = (InputAttackPosition[0]) - 65;
		int x = (InputAttackPosition[1]) - 48;

		
		while ((InputAttackPosition[0] < 65 || InputAttackPosition[0] > 74 || InputAttackPosition[1] < 48 || InputAttackPosition[1] > 57) || 
			strlen(InputAttackPosition) != 2 || (BattleField[y][x] == "X") || (BattleField[y][x] == "O"))
		{
			if ((InputAttackPosition[0] < 65 || InputAttackPosition[0] > 74 || InputAttackPosition[1] < 48 || InputAttackPosition[1] > 57) || strlen(InputAttackPosition) != 2)
			{
				printf("\n잘못된 좌표를 입력했습니다. 다시 입력해주세요. (세로 좌표는 대문자로 입력)");
				std::cin >> InputAttackPosition;
				std::cin.clear();
				std::cin.ignore(10000, '\n');

				y = InputAttackPosition[0] - 'A';
				x = InputAttackPosition[1] - '0';
			}
			else if ((BattleField[y][x] == "X") || (BattleField[y][x] == "O"))
			{
				printf("\n이미 공격한 좌표입니다. 다시 입력해주세요.");
				std::cin >> InputAttackPosition;
				std::cin.clear();
				std::cin.ignore(10000, '\n');

				y = InputAttackPosition[0] - 'A';
				x = InputAttackPosition[1] - '0';
			}

		}



		
		//	루프 빠져나와서 정상 공격 처리하는 부분




		if (BattleField[y][x] == ".")
		{
			printf("\n명중 실패! 빗나갔습니다.");
			BattleField[y][x] = "X";
			HiddenField[y][x] = "X";
			RemainShells--;
		}
		else if (BattleField[y][x] != ".")
		{
			printf("공격이 명중했습니다.");
			BattleField[y][x] = "O";
			HiddenField[y][x] = "O";
			RemainShells--;
		}

		printf("\n아무 키나 누르면 계속 진행합니다...");

		_getch();

		
	}
	if (CarrierHealth == 0 && BattleshipHealth == 0 && CruiserHealth == 0 && DestroyerHealth == 0)
	{
		printf("\n\n★★★ 모든 함선을 격침시켰습니다. 승리! ★★★");
	}
	else if (RemainShells <= 0)
	{
		system("cls");

		printf("--------------- [배틀쉽 게임] ---------------\n\n");

		printf(" "); // 가로좌표 패딩

		for (int e = 0; e < FieldSize; e++)
		{
			printf("%4d", Width[e]);
		}

		printf("\n\n"); // 높이 패딩

		for (int e = 0; e < FieldSize; e++)
		{
			Height[e] = 'A' + e; // ASCII code A 값에서 1만큼 증가시킴. 
			printf("%c", Height[e]);

			for (int f = 0; f < FieldSize; f++)
			{
				printf("%4s", BattleField[e][f].c_str()); // 실제 보는 맵
			}
			printf("\n\n"); // 가로 패딩
		}
		
		printf("\n\n===== 공격 횟수가 모두 소진되었습니다.. 패배 =====");
	}
	}

