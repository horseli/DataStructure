//void Union(LinkList La, LinkList Lb, LinkList Lc)
//{
//	LinkList p = La->next;
//	LinkList q = Lb->next;
//	int len_a = ListLength(La), len_b = ListLength(Lb), len_c = ListLength(Lc);
//	for (int t = 0; t < len_b; t++, q = q->next)
//	{
//		InsertElem(Lc, ++len_c, q->date);
//	}
//	q = Lb->next;
//	for (int i = 0; i < len_a; i++, p = p->next)
//	{
//		int t = 0;
//		for (int j = 0; j < len_b; j++, q = q->next)
//		{
//			if (q->date == p->date)
//			{
//				t = 1;
//				break;
//			}
//		}
//		q = Lb->next;
//		if (t == 0)
//			InsertElem(Lc, ++len_c, p->date);
//	}
//
//}
//void AddUnion(LinkList La, LinkList Lb, LinkList Lc)
//{
//	LinkList p = La->next, q = Lb->next, s = Lc->next;
//	SortList1(La);
//	SortList1(Lb);
//	int len_a = ListLength(La), len_b = ListLength(Lb), len_c = ListLength(Lc);
//	int i, j;
//	while (p&&q)
//	{
//		if (p->date <= q->date)
//		{
//			InsertElem(Lc, ++len_c, p->date);
//			p = p->next;
//		}
//		else {
//			InsertElem(Lc, ++len_c, q->date);
//			q = q->next;
//		}
//	}
//	while (p) {
//		InsertElem(Lc, ++len_c, p->date);
//		p = p->next;
//	}
//	while (q) {
//		InsertElem(Lc, ++len_c, q->date);
//		q = q->next;
//	}
//}
//
//
//
//void Plyadd(LinkList La, LinkList Lb)//a��b����ʽ��� ��a�ӵ�b
//{
//	/*�Ȱ�����Ķ���ʽ����*/
//	SortList(La);
//	SortList(Lb);
//	LinkList p = La->next, q = Lb->next, ha = La, hb = Lb;
//	for (; p&&q;)
//	{
//		cout << "&";
//		term&a = p->date, &b = q->date;//�����Ըı�ʵ��
//		if (a.ep > b.ep)  //ǰ��
//		{
//			cout << "%";
//			LinkList m = q->next, n = q;
//			q->next = ha->next;
//			ha->next = q;
//			hb = hb->next;
//			delete(n);
//			q = m;
//			ha = ha->next;
//		}
//		if (a.ep == b.ep)//��Ӳ�ͬʱ����
//		{
//			cout << "*";
//			a.co += b.co;
//			if (!a.co)
//			{
//				LinkList a1 = q, b1 = p;
//				p = p->next;
//				q = q->next;
//				delete(a1);
//				delete(b1);
//			}//�����Դ��룬���Ϊ0ʱ
//
//			else {
//				ha = ha->next;
//				p = p->next;
//				hb = hb->next;
//				q = q->next;
//			}
//		}
//		if (a.ep < b.ep)//La����
//		{
//			cout << "^";
//			ha = ha->next;
//			p = p->next;
//
//			/*else if(q->next){
//			hb = hb->next;
//			q = q->next;
//			}
//			else break;*/
//		}
//	}
//	if (q)
//	{
//		cout << "$";
//		ha->next = q;
//		cout << q->date.ep;
//	}
//}
//void ShowList(LinkList L)//����չʾ�˶���ʽ
//{
//	LinkList p = L->next, q = p->next;
//
//	for (int j = 1; j <= ListLength(L); j++, p = p->next)
//	{
//		char c = '+';//�����������
//					 //�����Դ���
//		if (p->date.co == 1)//��ϵ��Ϊ1��-1ʱʡ��
//			;
//		else if (p->date.co == -1)
//			cout << "-";
//		else cout << p->date.co;
//		if (p->date.ep == 0)//��ָ��Ϊ0��1ʱ�Ĵ���
//			;
//		else if (p->date.ep == 1)
//			cout << "*x";
//		else
//			cout << "*x^" << p->date.ep;
//		if (p->next&&p->next->date.co > 0)//��pָ����һ��Ϊ������pָ����һ������Ϊ��ʱ���+
//			cout << c;
//	}
//	cout << endl;
//}