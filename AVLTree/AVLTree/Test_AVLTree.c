#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// AVL_TREE
	// 좌우 서브 트리의 차가 2 이상이면 Rotation을 통해 높이 균형을 맞추는 트리
	// 높이가 더 높은 쪽에 회전을 줘서 균형을 맞춤
	// 다음 4가지 경우로 균형을 유지(삽입/삭제 시)

	// case LL:
	// 왼쪽 자식의 높이가 더 높고, 그의 왼쪽 자식의 높이도 높은 경우
	// case RR:
	// 오른쪽 자식의 높이가 더 높고, 그의 오른쪽 자식의 높이도 높은 경우
	// case LR:
	// 왼쪽 자식의 높이가 더 높고, 그의 오른쪽 자식의 높이가 높은 경우
	// case RL:
	// 오른쪽 자식의 높이가 더 높고, 그의 왼쪽 자식의 높이가 높은 경우

// 노드 구성
// 높이, 좌, 우 포인터
// key도

typedef struct tagNode
{
	int key;
	struct tagNode* left;
	struct tagNode* right;

	int height;
}Node;

Node* createNode(int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	node->height = 1;
	return node;
}

void freeTree(Node* root)
{
	if (root == NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

Node* getMinNode(Node* node)
{
	while (node != NULL && node->left != NULL)
		node = node->left;

	// min 존재하면 반환 
	// else NULL
	return node;
}

/// <summary>
/// 할당 되지 않은 노드는 높이: 0 그 외 높이 반환
/// </summary>
/// <param name="n">트리 특정 노드</param>
/// <returns></returns>
int getHeight(Node* n)
{
	return n == NULL ? 0 : n->height;
}

int getMax(int a, int b)
{
	return (a > b) ? a : b;
}

/// <summary>
/// 노드 재정렬 시 높이 맞추기. bottom -> top 순
/// 자식 노드가 바뀌거나 자식의 높이가 바뀔 때 계산되는 함수
/// </summary>
/// <param name="n"></param>
void updateHeight(Node* n)
{
	n->height = 1 + getMax(getHeight(n->left), getHeight(n->right));
}

Node* rotateLeft(Node* node)
{
	Node* rightChild = node->right;
	node->right = rightChild->left;
	rightChild->left = node;

	updateHeight(node);// 밑에부터 높이 갱신
	updateHeight(rightChild);// 새 루트는 나중에

	return rightChild;// 새 루트 반환(밖에서 부모와의 연결을 위해)
}

Node* rotateRight(Node* node)
{
	Node* leftChild = node->left;
	node->left = leftChild->right;
	leftChild->right = node;

	updateHeight(node);
	updateHeight(leftChild);

	return leftChild;
}

/// <summary>
/// 두 자식의 높이차 반환, NULL일 땐 자연스럽게 높이가 0
/// </summary>
/// <param name="node"></param>
/// <returns></returns>
int getBalanceFactor(Node* node)
{
	if (node == NULL) return 0;

	return getHeight(node->left) - getHeight(node->right);
}

Node* rebalance(Node* node)
{
	int bf = getBalanceFactor(node);

	// Left의 높이가 클 때
	if (bf > 1)
	{
		// case LR: 왼쪽 자식의 오른쪽 자식이 더 높을 때
		if (getBalanceFactor(node->left) < 0)
		{
			node->left = rotateLeft(node->left);
			// 이후 node 우회전이 필요하지만 밑에서 수행하기에 생략
		}
		// case LL: 왼쪽 자식의 왼쪽 자식이 더 높을 때
		return rotateRight(node);
	}
	// Right의 높이가 클 때
	else if (bf < -1)
	{
		// case RL: 오른쪽 자식의 왼쪽 자식이 더 높을 때
		if (getBalanceFactor(node->right) > 0)
		{
			node->right = rotateRight(node->right);
			// 이후 node 좌회전이 필요하지만 밑에서 수행하기에 생략
		}
		// case RR: 오른쪽 자식의 오른쪽 자식이 더 높을 때
		return rotateLeft(node);
	}
	// 두 자식의 차가 1이하
	else
		return node;
}

Node* insert(Node* node, int key)
{
	if (node == NULL) return createNode(key);

	// 삽입 기본 동작: 이진 탐색 트리와 같음
	if (key < node->key) node->left = insert(node->left, key);
	else if (key > node->key) node->right = insert(node->right, key);
	else return node;// 중복키

	updateHeight(node);// 자식 처리 끝났으니 내 높이 갱신
	return rebalance(node);// 균형 깨졌으면 회전하고 새 루트 혹은 노드 반환
}

Node* removeNode(Node* node, int key)
{
	if (node == NULL) return NULL;// 키 못찾을 때

	if (key < node->key) node->left = removeNode(node->left, key);
	else if (key > node->key) node->right = removeNode(node->right, key);
	// 찾은 경우
	else
	{
		// 자식이 0, 1개 있는 경우
		if (node->right == NULL || node->left == NULL)
		{
			Node* child = node->left != NULL ? node->left : node->right;
			free(node);
			return child;// 자식이 현재 노드 자리를 대신(없으면 NULL이)
		}

		// 자식이 2개인 경우(우측 최소 값이랑 개념적으로 swap 이후 최소 값 노드 삭제)
		Node* succ = node->right;
		succ = getMinNode(succ);
		node->key = succ->key;
		node->right = removeNode(node->right, succ->key);
		// 1) 이 친구도 removeNode로 재귀 삭제(우측 자식 존재 가능성 때문)
		// 2) 돌아오면서 후계자까지 가는 경로의 노드들이 updateHeight/rebalance 됨
	}

	updateHeight(node);
	return rebalance(node);
}

// ===================== 출력 / 검증 유틸 =====================

/// <summary>
/// 트리를 디렉터리 구조처럼 출력 (각 노드의 key, height, balance factor 표시)
/// prefix: 현재 줄 앞에 붙일 세로선 문자열
/// </summary>
static void printTreeRec(Node* node, const char* prefix, int isLast, const char* label)
{
	if (node == NULL) return;

	printf("%s%s%s%d (h=%d, bf=%d)\n",
		prefix, isLast ? "`-- " : "|-- ", label,
		node->key, node->height, getBalanceFactor(node));

	char childPrefix[256];
	snprintf(childPrefix, sizeof(childPrefix), "%s%s", prefix, isLast ? "    " : "|   ");

	// 왼쪽 자식이 있으면 오른쪽 자식은 마지막 줄이 아님
	if (node->left != NULL)
		printTreeRec(node->left, childPrefix, node->right == NULL, "L: ");
	if (node->right != NULL)
		printTreeRec(node->right, childPrefix, 1, "R: ");
}

void printTree(Node* root)
{
	if (root == NULL)
	{
		printf("  (empty)\n");
		return;
	}
	printf("  %d (h=%d, bf=%d)\n", root->key, root->height, getBalanceFactor(root));

	if (root->left != NULL)
		printTreeRec(root->left, "  ", root->right == NULL, "L: ");
	if (root->right != NULL)
		printTreeRec(root->right, "  ", 1, "R: ");
}

/// <summary>
/// AVL 성질 검증. 실제 높이를 반환하고, 문제가 있으면 *ok = 0
/// 1) BST 순서: min < key < max
/// 2) 저장된 height == 실제 높이
/// 3) |bf| <= 1
/// </summary>
static int checkAVLRec(Node* node, long long min, long long max, int* ok)
{
	if (node == NULL) return 0;

	if (node->key <= min || node->key >= max)
	{
		printf("  [ERROR] BST 순서 위반: key=%d\n", node->key);
		*ok = 0;
	}

	int lh = checkAVLRec(node->left, min, node->key, ok);
	int rh = checkAVLRec(node->right, node->key, max, ok);
	int real = 1 + getMax(lh, rh);

	if (node->height != real)
	{
		printf("  [ERROR] height 불일치: key=%d 저장=%d 실제=%d\n", node->key, node->height, real);
		*ok = 0;
	}
	if (lh - rh > 1 || lh - rh < -1)
	{
		printf("  [ERROR] 균형 깨짐: key=%d bf=%d\n", node->key, lh - rh);
		*ok = 0;
	}
	return real;
}

int checkAVL(Node* root)
{
	int ok = 1;
	checkAVLRec(root, (long long)INT_MIN - 1, (long long)INT_MAX + 1, &ok);
	return ok;
}

// ===================== 테스트 =====================

static int g_pass = 0;
static int g_fail = 0;

// 한 단계 실행 후 트리와 검증 결과 출력
static void showStep(const char* action, int key, Node* root)
{
	printf("\n> %s %d\n", action, key);
	printTree(root);
	if (!checkAVL(root)) printf("  !! AVL 성질 위반\n");
}

static Node* stepInsert(Node* root, int key)
{
	root = insert(root, key);
	showStep("insert", key, root);
	return root;
}

static Node* stepRemove(Node* root, int key)
{
	root = removeNode(root, key);
	showStep("remove", key, root);
	return root;
}

// 시나리오 마지막 상태 확인: 루트 key와 전체 높이 기대값 비교
static void expect(const char* name, Node* root, int rootKey, int height)
{
	int ok = checkAVL(root)
		&& root != NULL
		&& root->key == rootKey
		&& getHeight(root) == height;

	printf("\n  => [%s] %s (기대: root=%d, h=%d / 결과: root=%d, h=%d)\n",
		ok ? "PASS" : "FAIL", name, rootKey, height,
		root ? root->key : -1, getHeight(root));

	if (ok) g_pass++;
	else g_fail++;
}

static void title(const char* t)
{
	printf("\n==================================================\n");
	printf(" %s\n", t);
	printf("==================================================\n");
}

int main(void)
{
	Node* root;

	// ---------- 삽입 4가지 회전 ----------
	title("LL: 3 -> 2 -> 1 (rotateRight)");
	root = NULL;
	root = stepInsert(root, 3);
	root = stepInsert(root, 2);
	root = stepInsert(root, 1);
	expect("LL", root, 2, 2);
	freeTree(root);

	title("RR: 1 -> 2 -> 3 (rotateLeft)");
	root = NULL;
	root = stepInsert(root, 1);
	root = stepInsert(root, 2);
	root = stepInsert(root, 3);
	expect("RR", root, 2, 2);
	freeTree(root);

	title("LR: 3 -> 1 -> 2 (rotateLeft(left) + rotateRight)");
	root = NULL;
	root = stepInsert(root, 3);
	root = stepInsert(root, 1);
	root = stepInsert(root, 2);
	expect("LR", root, 2, 2);
	freeTree(root);

	title("RL: 1 -> 3 -> 2 (rotateRight(right) + rotateLeft)");
	root = NULL;
	root = stepInsert(root, 1);
	root = stepInsert(root, 3);
	root = stepInsert(root, 2);
	expect("RL", root, 2, 2);
	freeTree(root);

	// ---------- 삭제 ----------
	title("삭제 후 RR: 2,1,3,4 삽입 -> 1 삭제");
	root = NULL;
	root = stepInsert(root, 2);
	root = stepInsert(root, 1);
	root = stepInsert(root, 3);
	root = stepInsert(root, 4);
	root = stepRemove(root, 1);
	expect("remove -> RR", root, 3, 2);
	freeTree(root);

	title("삭제 후 자식 bf=0 (단일 회전이어야 함): 5,3,8,2,4 삽입 -> 8 삭제");
	root = NULL;
	root = stepInsert(root, 5);
	root = stepInsert(root, 3);
	root = stepInsert(root, 8);
	root = stepInsert(root, 2);
	root = stepInsert(root, 4);
	root = stepRemove(root, 8);
	expect("remove -> child bf 0", root, 3, 3);
	freeTree(root);

	title("자식 2개인 노드(루트) 삭제: 1~7 삽입 -> 4 삭제");
	root = NULL;
	for (int i = 1; i <= 7; i++) root = stepInsert(root, i);
	root = stepRemove(root, 4);
	expect("remove 2 children", root, 5, 3);
	freeTree(root);

	title("없는 키 삭제 / 중복 키 삽입: 1,2,3 -> remove 99 -> insert 2");
	root = NULL;
	root = stepInsert(root, 1);
	root = stepInsert(root, 2);
	root = stepInsert(root, 3);
	root = stepRemove(root, 99);
	root = stepInsert(root, 2);
	expect("not found / duplicate", root, 2, 2);
	freeTree(root);

	// ---------- 대량 테스트 (출력 없이 검증만) ----------
	title("대량: 1~1000 오름차순 삽입 후 짝수 전부 삭제");
	root = NULL;
	int bulkOk = 1;
	for (int i = 1; i <= 1000; i++)
	{
		root = insert(root, i);
		if (!checkAVL(root)) { bulkOk = 0; break; }
	}
	printf("  삽입 후 높이: %d (AVL 이론상 최대 약 1.44*log2(n) ~ 14)\n", getHeight(root));
	for (int i = 2; i <= 1000 && bulkOk; i += 2)
	{
		root = removeNode(root, i);
		if (!checkAVL(root)) bulkOk = 0;
	}
	printf("  삭제 후 높이: %d\n", getHeight(root));
	printf("\n  => [%s] bulk insert/remove\n", bulkOk ? "PASS" : "FAIL");
	if (bulkOk) g_pass++;
	else g_fail++;
	freeTree(root);

	printf("\n==================================================\n");
	printf(" 결과: PASS %d / FAIL %d\n", g_pass, g_fail);
	printf("==================================================\n");

	return g_fail == 0 ? 0 : 1;
}