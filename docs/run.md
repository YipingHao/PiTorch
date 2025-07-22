# ���к͵��Խű�run.sh��ʹ��ָ��

���ű��������� `./test/test.exe` ����֧�ֲ������롢���·��ָ�����Լ� GDB ���ԡ�

---

##  �����÷�

```bash
bash run.sh [ѡ��]
```

##  ֧�ֵ�ѡ��

- `-g [gdb����...]`  
  ʹ�� GDB ���Գ��� `test.exe`�����Ը��� GDB �Ĳ�������ѡ����ʾ�����·���

- `-i <�����ļ�>`  
  ָ�������ļ�·����Ĭ��ֵΪ `parameter/parameter.txt`��  
  ����`-i data/input.txt`

- `-I <�ļ���>`  
  ָ�������ļ��������Զ����� `./parameter/` ǰ׺����  
  ����`-I myparam.txt` ��ʹ�� `./parameter/myparam.txt` ��Ϊ���롣

- `-o <���Ŀ¼>`  
  ָ�����Ŀ¼��Ĭ��ֵΪ `output/`�����Ŀ¼�����ڣ��ű��᳢���Զ�������

- `-h`  
  ��ʾ������Ϣ���˳���

---

##  ʹ�þ���

1. **�������У�ʹ��Ĭ�ϲ���**
   ```bash
   bash run.sh
   ```
   �ȼ��ڣ�
   ```bash
   ./test/test.exe parameter/parameter.txt output/
   ```

2. **ָ�������ļ������Ŀ¼**
   ```bash
   bash run.sh -i myinput.txt -o myresult/
   ```
   ���У�
   ```bash
   ./test/test.exe myinput.txt myresult/
   ```

3. **ָ�������ļ������Զ���ǰ׺��**
   ```bash
   bash run.sh -I test1.txt
   ```
   ���У�
   ```bash
   ./test/test.exe ./parameter/test1.txt output/
   ```

4. **GDB ��������**
   ```bash
   bash run.sh -g
   ```
   ���ȼ���:
   ```bash
   gdb --args ./test/test.exe parameter/parameter.txt output/
   ```

5. **GDB ���Բ��Զ��� GDB ����**
   ```bash
   bash run.sh -g -q
   ```
   ִ�У�
   ```bash
   gdb -q --args ./test/test.exe parameter/parameter.txt output/
   ```

---

##  ע������

- ���Ŀ¼�粻���ڣ��ű����Զ����Դ�������ʧ�ܣ�����Ȩ�ޣ��ᱨ���˳���
- `-g` ��Ĳ�����ԭ�����ݸ� GDB��
- ���������������Ϊ�����ȱʧʱ�ᱨ�����ѡ�
- `-h` ����ʱ�鿴������Ϣ��

---

�����һ���Զ�����������⣬��ο��ű�ע�ͻ�����Ŀά������ϵ��