#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1005;

struct Pair{
	int x, y;
} pn[MAXN];

int q[MAXN];
int px[MAXN], py[MAXN];
int n, w, h, s, ans;

bool cmp(Pair a, Pair b){
	return a.x < b.x;
}

void check()
{
	sort(pn, pn + s, cmp);
	//0 ~ s 
	int h = 0, t = -1, j = 1;
	for (int i = 0; i < s-1; i ++){
		while (h <= t && q[h] <= i) h ++;
		while (j < s && (h > t || pn[q[h]].y >= pn[j].x - pn[i].x)){
			q[++ t] = j ++;
			while (h < t && pn[q[t]].y <= pn[q[t-1]].y){
				q[t-1] = q[t]; t --;
			}
		}
		int w = pn[q[h]].y;
		if (pn[s-1].x - pn[i].x < w)
			w = pn[s-1].x - pn[i].x;
		if (w > ans) ans = w;
	}
}

int main()
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d%d%d", &n, &w, &h);
	for (int i = 0; i < n; i ++)
		scanf("%d%d", &px[i], &py[i]);
	ans = 0;
	for (int i = 0; i < n; i ++){
		int x0 = px[i];
		int y0 = py[i];
		//x >= x0
		s = 0;
		for (int j = 0; j < n; j ++)	// 找到在(x0, y0)右边的点，横坐标改为相对坐标
			if (px[j] > x0)
				pn[s ++] = (Pair){py[j], px[j] - x0};
		pn[s ++] = (Pair){0, w - x0};	// 横轴最右边的点
		pn[s ++] = (Pair){h, w - x0};	// 纵轴最大值、横轴相对最大值
		check();
		for (int j = 0; j < n; j ++)
			pn[j].x = h - pn[j].x;
		check();
		//x <= x0
		s = 0;
		for (int j = 0; j < n; j ++)
			if (px[j] < x0)
				pn[s ++] = (Pair){py[j], x0 - px[j]};
		pn[s ++] = (Pair){0, x0};
		pn[s ++] = (Pair){h, x0};
		check();
		for (int j = 0; j < n; j ++)
			pn[j].x = h - pn[j].x;
		check();
		//y >= y0
		s = 0;
		for (int j = 0; j < n; j ++)
			if (py[j] > y0)
				pn[s ++] = (Pair){px[j], py[j] - y0};
		pn[s ++] = (Pair){0, h - y0};
		pn[s ++] = (Pair){w, h - y0};
		check();
		for (int j = 0; j < n; j ++)
			pn[j].x = w - pn[j].x;
		check();
		//y <= y0
		s = 0;
		for (int j = 0; j < n; j ++)
			if (py[j] < y0)
				pn[s ++] = (Pair){px[j], y0 - py[j]};
		pn[s ++] = (Pair){0, y0};
		pn[s ++] = (Pair){w, y0};
		check();
		for (int j = 0; j < n; j ++)
			pn[j].x = w - pn[j].x;
		check();
	}
	printf("%d\n", ans);
	return 0;
}