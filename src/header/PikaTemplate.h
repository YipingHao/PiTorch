#ifndef PikaTemplateuie4q3y89q34qerifqer89rt41389th89adfa
#define PikaTemplateuie4q3y89q34qerifqer89rt41389th89adfa
#include<stdio.h>
#include<stdlib.h>
#include <utility>
#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif
#include"../../extern/lexical/dictionary.h"
namespace Pikachu
{
	class PikaError
	{
	public:
		PikaError(const char* Source, const char* Error, int Code);
		PikaError(const PikaError& Old, const char* prefix);
		~PikaError();
		void show(FILE* fp)const;
	private:
		char* source;
		char* error;
		int code;
	};
}
namespace Pikachu
{
	typedef long int sint;

	template <class T> class vector
	{
	protected:
		size_t Count;
		size_t Capacity;
		T* content;
	public:
		vector();
		~vector();
		void clear(void);
		void copy(const vector<T>& source);
		void append(const vector<T>& source);
		void shrink(size_t site);
		size_t capacity(void) const { return Capacity; }
		size_t count(void) const{return Count;}
		void recapacity(size_t NewSize);
		void recount(size_t NewCount);
		void append(const T& element);
		sint search(const T& element);
		size_t SearchAppend(const T& element);
		size_t pop(T& element);
		size_t top(T& element);
		void pop(void);
		size_t append(void);
		void swap(vector<T>& other);
		const T* array(void) const;
		T* array(void);
		const T* array(size_t offset)const;
		T* array(size_t offset);
		T const& operator[](size_t target) const { return content[target]; }
		T& operator[](size_t target) { return content[target]; }
		void value(const T& element);
		T const& top(void) const;
		T& top(void);
	};
	template <class T> class array
	{
	protected:
		size_t Length;
		T* content;
	public:
		array();
		~array();
		size_t length(void) const;
		T* vector(void);
		T* ptr(size_t offset);
		const T* ptr(size_t offset) const;
		T& operator[](size_t target);
		T& operator[](const size_t target) const;
		void value(const T& element);
		void Malloc(size_t NewSize);
		void Realloc(size_t NewSize);
		void Free(void);
	};
	template <class T> class buffer
	{
	protected:
		size_t Rear;
		size_t Capacity;
		size_t Head;
		T* content;
	public:
		buffer();
		~buffer();
		void clear(void);
		void append(const buffer<T>& other);
		size_t append(const T& element);
		size_t expand(void);
		void expand(const size_t L);
		bool dequeue(T& out);
		bool backspace(T& in);
		bool backspace(buffer<T>& in);
		T* array(void);
		const T* array(void) const;
		size_t count(void) const;
		size_t rear(void) const;
		size_t capacity(void) const;
		size_t head(void) const;
		T& operator[](size_t target) const;
	};
	template <class T> class list
	{
	private:
		size_t Count;
		size_t Capacity;
		size_t Fisrt;
		T** content;
		size_t* Next;
	public:

	};

}
namespace Pikachu
{
	template <class V, class A> class graph1
	{
	public:
		struct vortex
		{
			size_t InDegree;
			size_t OutDegree;
			size_t InCapacity;
			size_t OutCapacity;
			size_t* In;
			size_t* Out;
			size_t Next;
			V* content;
			void refresh(void);
			void ruin(void);
			size_t AppendIn(size_t II);
			size_t AppendOut(size_t II);
		};
		struct arc
		{
			size_t from;
			size_t to;
			size_t FromSite;
			size_t ToSite;
			A* content;
			void refresh(void)
			{
				from = _uintMax_;
				to = _uintMax_;
				FromSite = _uintMax_;
				ToSite = _uintMax_;
				content = NULL;
			}
		};
	public:
		graph1();
		~graph1();
		size_t AppendVortex(void);
		size_t AppendArc(void);
		size_t append(size_t from, size_t to, A* C);
		size_t append(V* C);
		void deleteArc(size_t site);
		vortex& SV(const size_t No);
		arc& SA(const size_t No);
	private:
		array<arc> arcs;
		array<vortex> vertice;
		size_t firstVainArc;
		size_t firstVainVortex;
		size_t arcsCount;
		size_t vortexCount;
	};
	template <class V> class graph2
	{
	public:
		struct vortex
		{
			size_t InDegree;
			size_t OutDegree;
			size_t InCapacity;
			size_t OutCapacity;
			size_t* In;
			size_t* Out;
			V* content;

			size_t Next;
			//bool Vain;
			void refresh(void);
			void ruin(void);
			size_t AppendIn(size_t II);
			size_t AppendOut(size_t II);
			void RecountIn(size_t count);
			void RecountOut(size_t count);
			void SetValid(void);
			void SetNotValid(void);
			bool IfValid(void) const;
			void copy(const vortex& source);

			void Demo(FILE* fp)const;
			size_t SearchIn(size_t label) const;
			size_t SearchOut(size_t label) const;
			size_t SearchIn(size_t label, const char* error) const;
			size_t SearchOut(size_t label, const char* error) const;
			void ShrinkIn(size_t site);
			void ShrinkOut(size_t site);
		};
	public:
		graph2();
		~graph2();
		void clear(void);
		size_t AppendVortex(void);
		void append(size_t from, size_t to);
		void append(size_t srcL, size_t srcR, size_t to);
		void append(size_t srcL, size_t srcM, size_t srcR, size_t to);
		void append(const graph2& source, vector<size_t>& label);
		size_t capacity(void)const;
		size_t append(V* C);
		size_t MoveAppend(V* C);
		vortex& SV(const size_t No);
		graph2<V>* copy(void) const;
		void copy(const graph2<V>& source);
		vortex& operator[](size_t target);
		vortex& In(size_t source, size_t No);
		const vortex& operator[](size_t target) const;

		void BFTforward(vector<size_t>& label, buffer<size_t>& queue) const;
		void BFTbackward(vector<size_t>& label, buffer<size_t>& queue) const;
		void path(vector<size_t>& label, buffer<size_t>& queue, size_t from, size_t to) const;
		void TopologicalSorting(vector<size_t>& sequence)const;
		void TopoSortDFT(vector<size_t>& sequence)const;// Topological Sorting Depth First
		void TopologicalSortingBack(vector<size_t>& sequence)const;
		void SortingShrink(vector<size_t>& label, vector<size_t>& sequence) const;
		void TraverseInitial(vector<size_t>& label, vector<size_t>& stack) const;
		void TraverseNextBack(vector<size_t>& label, vector<size_t>& stack) const;

		void OutputGive(vector<size_t>& label) const;
		void OutputCut(vector<size_t>& label, size_t target) const;

		void lift(size_t middle, size_t down);
		void lift(size_t up, size_t middle, size_t down);
		void LiftLeft(size_t middle);
		void LiftRight(size_t middle);
		size_t LiftLeft(size_t middle, size_t OldOutput);
		size_t LiftRight(size_t middle, size_t OldOutput);
		void VertexDelete(size_t targer);
		void ArcDelete(size_t from, size_t to);
	private:
		array<vortex> vertice;
		size_t firstVainVortex;
		size_t vortexCount;
	};

	template <class V> class iteratorS
	{
	public:
		iteratorS()
		{
		}
		~iteratorS()
		{
		}
		struct infor
		{
			int state;
			V* target;
		};
		int& state(void) { return stack.top().state; }
		V*& target(void) { return stack.top().target; }
		bool still(void) { return stack.count() != 0; };
		void clear(void) { stack.clear(); }
		void pop(void) {stack.pop();}
		void append(V* ele)
		{
			infor II;
			II.state = 0;
			II.target = ele;
			stack.append(II);
			return;
		}
		void append(V* ele, int SS)
		{
			infor II;
			II.state = SS;
			II.target = ele;
			stack.append(II);
			return;
		}
	private:
		vector<infor> stack;
		
	};

	template <class V> class graph;
	//CRTP （Curiously Recurring Template Pattern）
	// 开发者必须在派生类的析构函数中添加以下语句：infor = (void*)this;
// Developer must add the following statement in the derived class destructor: infor = (void*)this;
	template <class V> class vortex
	{
	protected:
		size_t label_site;
		vector<V*>out;
		vector<V*>in;
		V* all;
	public:
		int label_2;
		bool label_3;
		void* infor;
		size_t temp;
		typedef V Vextern;
	public:
		//template <typename... Args>
		vortex()//(Args&&... args) //: V(std::forward<Args>(args)...)
		{
			temp = 0;
			label_site = 0;
			label_2 = 0;
			label_3 = false;
			infor = NULL;
		}
		~vortex();
		//void value(const V& source);
		void CopyCore(const Vextern& source);
		void CopyToCore(Vextern& dst) const;
		void demo(FILE* fp)const;
		size_t site(void) const { return label_site;}
		//void PushIn(Vextern* stack);
		//void PushOut(Vextern* stack);
		size_t AppendIn(Vextern* II);
		size_t AppendOut(Vextern* II);
		size_t SearchIn(Vextern* label) const;
		size_t SearchOut(Vextern* label) const;
		size_t SearchInExcept(Vextern* label) const;
		size_t SearchOutExcept(Vextern* label) const;
		void ShrinkIn(size_t site);
		void ShrinkOut(size_t site);
		Vextern* In(size_t site) { return in[site]; }
		Vextern* Out(size_t site) { return out[site]; }
		size_t InDegree(void) const { return in.count(); }
		size_t OutDegree(void)const { return out.count();}
		friend class graph<V>;
		static void BackNext(iteratorS<Vextern>& iter);
	};
	template <class V> class graph
	{
	public:
		typedef V VExtern;
	protected:
		vector<VExtern*> content;
		vector<size_t> vain;
	public:
		graph();
		~graph();
		void copy(const graph<V>& src);
		void clear(void);
		size_t count(void) const { return content.count(); }
		VExtern*& operator [](size_t site) {return content[site];}
		VExtern* const & operator [](size_t site) const { return content[site]; }

		void ArcDelete(VExtern* src, VExtern* dst);
		void ArcAdd(VExtern* src, VExtern* dst);
		void ArcAdd(VExtern* srcL, VExtern* srcR, VExtern* dst);
		void ArcAdd(VExtern* srcL, VExtern* srcM, VExtern* srcR, VExtern* dst);
		void lift(VExtern* target, VExtern* src);// middle ,down
		void lift(VExtern* dst, VExtern* target, VExtern* src);
		// dst:up, target:middle, src:down
		void ruin(size_t i);
		void operator << (VExtern* in);
		void append(VExtern* in);
		void append(graph<V>& in);
		void compress(void);

		void TopoSortDFS(vector<VExtern*>& sequence)const;
		void TopoSortBFS(vector<VExtern*>& sequence)const;
		void TopoSortDFSBack(vector<VExtern*>& sequence)const;
		void TopoSortBFSBack(vector<VExtern*>& sequence)const;

		void BFTbackward(vector<bool>& label, buffer<VExtern*>&queue)const;
		void Shrink(const vector<bool>& label, vector<VExtern*>& sequence) const;
		
		void OutputGive(vector<size_t>& label) const;
		void OutputCut(vector<size_t>& label, size_t target)const;
	};
	

}
namespace Pikachu
{
	template <class V, class A> class vertex;
	template <class V, class A> class arc;
	template <class V, class A> class vertex : public V
	{
		size_t temp;
		size_t Gsite;
		int label_2;
		bool label_3;
		void* infor;
		vector<arc<V,A>*> arcs;
		size_t ind;
		size_t outd;
		size_t totald;
	public:
		vertex()
		{
			temp = 0;
			Gsite = 0;
			label_2 = 0;
			label_3 = false;
			infor = NULL;

			ind = 0;
			outd = 0;
			totald = 0;
		}
		~vertex()
		{
			size_t i;
			for (i = 0; i < arcs.count(); i++)
				delete arcs[i];
		}
		void compress(void)
		{
			size_t i, site;
			site = 0;
			for (i = 0; i < arcs.count(); i++)
			{
				if (arcs[i] != NULL)
				{
					arcs[site] = arcs[i];
					if (arcs[site]->Isfrom(this))
						arcs[site]->siteF = site;
					else
						arcs[site]->siteT = site;
					site += 1;
				}
			}
			arcs.recount(site);
			return;
		}
	};
	template <class V, class A> class arc : public A
	{
		vertex<V, A>*from;
		vertex<V, A>*to;
		size_t siteF;
		size_t siteT;
	public:
		arc(vertex<V, A>* src, vertex<V, A>*dst)
		{
			from = src;
			to = dst;
			
			src->outd += 1;
			src->totald += 1;
			siteF = src->arcs.count();
			src->arcs.append(this);

			dst->ind += 1;
			dst->totald += 1;
			siteT = dst->arcs.count();
			dst->arcs.append(this);
		}
		~arc()
		{
			from->outd -= 1;
			from->totald -= 1;
			from->arcs[siteF] = NULL;

			to->ind -= 1;
			to->totald -= 1;
			to->arcs[siteT] = NULL;
		}
		bool Isfrom(vertex<V, A>* right)
		{
			return from == right;
		}
	};

	template <class V, class A> class Dgraph
	{
	private:
		vector<vertex<V, A>*> content;
		vector<size_t> vain;
	public:
		Dgraph()
		{

		}
		~Dgraph()
		{
			clear();
		}
		void copy(const Dgraph<V, A>& src)
		{
			clear();
		}
		void clear(void)
		{
			size_t i;
			for (i = 0; i < content.count(); i++)
				delete content[i];
			content.clear();
			vain.clear();
		}
		void append(vortex<V>* src)
		{
			size_t site;
			if (vain.pop(site) != 0)
			{
				content[site] = src;
			}
			else
			{
				content.append(src);
				site = content.count() - 1;
			}
			src->label_site = site;
		}
		void append(graph<V>& src)
		{
			size_t i;
			for (i = 0; i < src.content.count(); i++)
			{
				if (src.content[i] != NULL) append(src.content[i]);
			}
			src.content.clear();
			src.vain.clear();
		}
	};
}
namespace Pikachu
{
	template <class T> vector<T>::vector()
	{
		Count = 0;
		Capacity = 0;
		content = NULL;
	}
	template <class T> vector<T>::~vector()
	{
		Count = 0;
		Capacity = 0;
		free(content);
		content = NULL;
	}
	template <class T> void vector<T>::copy(const vector<T>& source)
	{
		size_t i;
		Count = source.Count;
		Capacity = Count;
		content = (T*)realloc(content, Capacity * sizeof(T));
		for (i = 0; i < Count; i++)
			content[i] = source.content[i];
	}
	template <class T> void vector<T>::append(const vector<T>& source)
	{
		size_t i, NewCount;
		NewCount = Count + source.Count;
		if (NewCount > Capacity)
		{
			content = (T*)realloc(content, NewCount * sizeof(T));
			Capacity = NewCount;
		}
		for (i = 0; i < source.Count; i++)
			content[i + Count] = source.content[i];
		Count = NewCount;
	}
	template <class T> void vector<T>::append(const T& element)
	{
		size_t should;
		should = append();
		content[should] = element;
		//return should;
	}
	template <class T> void vector<T>::shrink(size_t site)
	{
		size_t i;
		for (i = site + 1; i < Count; i++)
		{
			content[i - 1] = content[i];
		}
		Count -= 1;
	}
	template <class T> sint vector<T>::search(const T& element)
	{
		sint i;
		for (i = 0; i < Count; i++)
		{
			if (content[i] == element) return i;
		}
		return -1L;
	}
	template <class T> size_t vector<T>::SearchAppend(const T& element)
	{
		size_t i, j;
		const T* temp;
		for (i = 0; i < Count; i++)
		{
			if (content[i] == element) return i;
		}
		append(element);
		return Count - 1;
	}
	template <class T> void vector<T>::clear(void)
	{
		Count = 0;
	}
	template <class T> void vector<T>::recount(size_t NewCount)
	{
		if (NewCount > Capacity)
		{
			//std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< std::endl;
			//std::cout << "NewCount: " << NewCount << "Capacity: " << Capacity << std::endl;
			//std::cout << "old content: " << content << std::endl;
			content = (T*)realloc(content, NewCount * sizeof(T));
			//std::cout << "new content: " << content << std::endl;
			Capacity = NewCount;
		}
		Count = NewCount;
	}
	template <class T> void vector<T>::recapacity(size_t NewSize)
	{
		if (NewSize <= Count) Count = NewSize;
		content = (T*)realloc(content, NewSize * sizeof(T));
		Capacity = NewSize;
	}
	template <class T> size_t vector<T>::pop(T& element)
	{
		if (Count != 0)
		{
			Count -= 1;
			element = content[Count];
			return Count + 1;
		}
		return Count;
	}
	template <class T> size_t vector<T>::top(T& element)
	{
		if (Count != 0)
		{
			element = content[Count - 1];
		}
		return Count;
	}
	template <class T> void vector<T>::pop(void)
	{
		if (Count != 0) Count -= 1;
	}
	template <class T> size_t vector<T>::append(void)
	{
		size_t should, new_size;
		if (Count >= Capacity)
		{
			new_size = (Capacity + Capacity / 4 + 8);
			content = (T*)realloc(content, new_size * sizeof(T));
			Capacity = new_size;
		}
		should = Count;
		Count += 1;
		return should;
	}
	template <class T> void vector<T>::swap(vector<T>& other)
	{
		T* middle;
		middle = other.content;
		other.content = content;
		content = middle;

		size_t MM;

		MM = other.Count;
		other.Count = Count;
		Count = MM;

		MM = other.Capacity;
		other.Capacity = Capacity;
		Capacity = MM;
	}
	template <class T> const T* vector<T>::array(void) const
	{
		return content;
	}
	template <class T> T* vector<T>::array(void)
	{
		return content;
	}
	template <class T> const T* vector<T>::array(size_t offset)const
	{
		return content + offset;
	}
	template <class T> T* vector<T>::array(size_t offset)
	{
		return content + offset;
	}
	template <class T> void vector<T>::value(const T& element)
	{
		size_t i;
		for (i = 0; i < Count; i++)
			content[i] = element;
	}
	template <class T> T const & vector<T>::top(void) const
	{
		size_t target;
		target = Count != 0 ? Count - 1 : 0;
		return content[target];
	}
	template <class T> T& vector<T>::top(void)
	{
		size_t target;
		target = Count != 0 ? Count - 1 : 0;
		return content[target];
	}



	template <class T> array<T>::array()
	{
		Length = 0;
		content = NULL;
	}
	template <class T> array<T>::~array()
	{
		Length = 0;
		free(content);
		content = NULL;
	}
	template <class T> size_t array<T>::length(void) const
	{
		return Length;
	}
	template <class T> T* array<T>::vector(void)
	{
		return content;
	}
	template <class T> T* array<T>::ptr(size_t offset)
	{
		return content + offset;
	}
	template <class T> const T* array<T>::ptr(size_t offset) const
	{
		return content + offset;
	}
	template <class T> T& array<T>::operator[](size_t target)
	{
		return content[target];
	}
	template <class T> T& array<T>::operator[](const size_t target) const
	{
		return content[target];
	}
	template <class T> void array<T>::Malloc(size_t NewSize)
	{
		Length = NewSize;
		content = (T*)malloc(NewSize * sizeof(T));
	}
	template <class T> void array<T>::Realloc(size_t NewSize)
	{
		content = (T*)realloc(content, NewSize * sizeof(T));
		Length = NewSize;
	}
	template <class T> void array<T>::Free(void)
	{
		Length = 0;
		free(content);
		content = NULL;
	}
	template <class T> void array<T>::value(const T& element)
	{
		size_t i;
		for (i = 0; i < Length; i++)
			content[i] = element;
	}


	template <class T> buffer<T>::buffer()
	{
		Rear = 0;
		Capacity = 0;
		Head = 0;
		content = NULL;
	}
	template <class T> buffer<T>::~buffer()
	{
		Rear = 0;
		Capacity = 0;
		Head = 0;
		free(content);
		content = NULL;
	}
	template <class T> void buffer<T>::append(const buffer<T>& other)
	{
		size_t L, i;
		L = other.count();
		if (Rear + L > Capacity)
		{
			content = (T*)realloc(content, (Capacity + L + 4) * sizeof(T));
			Capacity = Capacity + L + 4;
		}
		for (i = 0; i < L; i++) content[i + Rear] = other.content[i + other.Head];
		Rear += L;
		return;
	}
	template <class T> size_t buffer<T>::append(const T& element)
	{
		size_t should;
		should = expand();
		content[should] = element;
		return should;
	}
	template <class T> void buffer<T>::clear(void)
	{
		Head = 0;
		Rear = 0;
	}
	template <class T> size_t buffer<T>::expand(void)
	{
		size_t should, i, new_size;
		if (Rear >= Capacity)
		{
			new_size = (Capacity + Capacity / 4 + 8);
			content = (T*)realloc(content, new_size * sizeof(T));
			Capacity = new_size;
		}
		should = Rear;
		Rear += 1;
		return should;
	}
	template <class T> void buffer<T>::expand(size_t L)
	{
		if (Rear + L > Capacity)
		{
			content = (T*)realloc(content, (Capacity + L + 4) * sizeof(T));
			Capacity = Capacity + L + 4;
		}
		return;
	}
	template <class T> bool buffer<T>::dequeue(T& out)
	{
		if (Head < Rear)
		{
			out = content[Head];
			Head += 1;
			return true;
		}
		return false;
	}
	template <class T> bool buffer<T>::backspace(T& in)
	{
		if (Head != 0)
		{
			Head -= 1;
			content[Head] = in;
			return true;
		}
		return false;
	}
	template <class T> bool buffer<T>::backspace(buffer<T>& in)
	{
		size_t i, LL;
		LL = in.Rear - in.Head;
		if (LL <= Head)
		{
			Head -= LL;
			for (i = 0; i < LL; i++)
			{
				content[Head + i] = in[in.Head + i];
			}
			in.clear();
			return true;
		}
		return false;
	}
	template <class T> T* buffer<T>::array(void)
	{
		//append('\0');
		return content + Head;
	}
	template <class T> const T* buffer<T>::array(void) const
	{
		return content + Head;
	}
	template <class T> size_t buffer<T>::count(void) const
	{
		return (size_t)(Rear - Head);
	}
	template <class T> size_t buffer<T>::rear(void) const
	{
		return Rear;
	}
	template <class T> size_t buffer<T>::capacity(void) const
	{
		return Capacity;
	}
	template <class T> size_t buffer<T>::head(void) const
	{
		return Head;
	}
	template <class T> T& buffer<T>::operator[](size_t target) const
	{
		return content[target];
	}

	





}
namespace Pikachu
{
	template <class V> graph<V>::graph()
	{

	}
	template <class V> graph<V>::~graph()
	{
		clear();
	}
	template <class V> void graph<V>::copy(const graph<V>& src)
	{
		VExtern* now, *srcV;
		size_t i, j, site;
		clear();
		vain.recount(src.vain.count());
		vain.copy(vain);
		content.recount(src.content.count());
		for (i = 0; i < src.content.count(); i++)
		{
			srcV = src[i];
			if (srcV != NULL)
			{
				//now = new VExtern;
				//now->copy(*srcV);
				now = srcV->copy();
				content[i] = now;
				now->label_site = i;
			}
			else content[i] = NULL;
		}
		for (i = 0; i < src.content.count(); i++)
		{
			srcV = src[i];
			if (srcV != NULL)
			{
				now = content[i];
				for (j = 0; j < now->in.count(); j++)
				{
					site = srcV->in[j]->label_site;
					now->in[j] = content[site];
				}
				for (j = 0; j < now->out.count(); j++)
				{
					site = srcV->out[j]->label_site;
					now->out[j] = content[site];
				}
			}
		}
	}
	template <class V> void graph<V>::clear(void)
	{
		size_t i;
		for (i = 0; i < content.count(); i++)
			delete content[i];
		content.clear();
		vain.clear();
	}
	template <class V> void graph<V>::ruin(size_t i)
	{
		delete content[i];
		content[i] = NULL;
		vain.append(i);
	}
	template <class V> void graph<V>::append(VExtern* src)
	{
		size_t site;
		if (vain.pop(site) != 0)
		{
			content[site] = src;
		}
		else
		{
			content.append(src);
			site = content.count() - 1;
		}
		src->label_site = site;
	}
	template <class V> void graph<V>::operator<<(VExtern* src)
	{
		append(src);
	}
	template <class V> void graph<V>::append(graph<V>& src)
	{
		size_t i;
		for (i = 0; i < src.content.count(); i++)
		{
			if (src[i] != NULL) append(src[i]);
		}
		src.content.clear();
		src.vain.clear();
	}
	template <class V> void graph<V>::compress(void)
	{
		size_t i, site;
		//VExtern* now;
		vain.clear();
		site = 0;
		for (i = 0; i < content.count(); i++)
		{
			if (content[i] != NULL)
			{
				content[site] = content[i];
				content[site]->label_site = site;
				site += 1;
			}
		}
		content.recount(site);
		return;
	}

	template <class V> void graph<V>::ArcDelete(VExtern* src, VExtern* dst)
	{
		size_t T, F;
		T = dst->SearchIn(src);
		if (T == dst->in.count())
		{
			hyperlex::dictionary* error;
			error = new hyperlex::dictionary;
			error->append("location", "graph<V>::ArcDelete");
			error->append("error", "T == vertice[to].InDegree");
			error->append("T", T);
			throw error;
		}
		F = src->SearchOut(dst);
		if (F == src->out.count())
		{
			hyperlex::dictionary* error;
			error = new hyperlex::dictionary;
			error->append("location", "graph<V>::ArcDelete");
			error->append("error", "T == vertice[to].InDegree");
			error->append("T", T);
			throw error;
		}
		
		dst->ShrinkIn(T);
		src->ShrinkOut(F);
	}
	template <class V> void graph<V>::ArcAdd(VExtern* src, VExtern* dst)
	{
		src->out.append(dst);
		dst->in.append(src);
	}
	template <class V> void graph<V>::ArcAdd(VExtern* srcL, VExtern* srcR, VExtern* dst)
	{
		srcL->out.append(dst);
		dst->in.append(srcL);

		srcR->out.append(dst);
		dst->in.append(srcR);
	}
	template <class V> void graph<V>::ArcAdd(VExtern* srcL, VExtern* srcM, VExtern* srcR, VExtern* dst)
	{
		srcL->out.append(dst);
		dst->in.append(srcL);

		srcM->out.append(dst);
		dst->in.append(srcM);

		srcR->out.append(dst);
		dst->in.append(srcR);
	}

	template <class V> void graph<V>::TopoSortDFS(vector<VExtern*>& sequence)const
	{
		vector<VExtern*> stack;
		size_t i;
		VExtern* now;
		VExtern* head;
		VExtern* next;
		vector<size_t> label;
		label.recount(content.count());
		sequence.clear();
		//compress();
		for (i = 0; i < content.count(); i++)
		{
			now = content[i];
			label[i] = 0;
			if (now != NULL)
			{
				label[i] = now->in.count();
				if (label[i] == 0) stack.append(now);
			}
		}
		while (stack.pop(head) != 0)
		{
			sequence.append(head);
			for (i = 0; i < head->out.count(); i++)
			{
				next = head->out[i];
				if (label[next->site()] == 0)
				{
					throw PikaError("graph<V>::TopoSortDFS", "label[next] == 0", next->site());
				}
				label[next->site()] -= 1;
				if (label[next->site()] == 0)
				{
					stack.append(next);
				}
			}
		}
	}
	template <class V> void graph<V>::TopoSortBFS(vector<VExtern*>& sequence)const
	{
		buffer<VExtern*> stack;
		size_t i;
		VExtern* head;
		VExtern* now;
		VExtern* next;
		vector<size_t> label;
		label.recount(content.count());
		//compress();
		sequence.clear();
		for (i = 0; i < content.count(); i++)
		{
			now = content[i];
			label[i] = 0;
			if (now != NULL)
			{
				label[i] = now->in.count();
				if (label[i] == 0) stack.append(now);
				//if (label[i] == 0) printf("now->site()%zu\n", now->site());
			}
		}
		while (stack.dequeue(head))
		{
			sequence.append(head);
			//printf("head->site()%zu\n", head->site());
			for (i = 0; i < head->out.count(); i++)
			{
				next = head->out[i];
				//printf("\t [%zu] next->site()%zu\n", i, next->site());
				if (label[next->site()] == 0)
				{
					throw PikaError("TopoSortDFS", "label[next] == 0", next->site());
				}
				label[next->site()] -= 1;
				if (label[next->site()] == 0)
				{
					stack.append(next);
				}
			}
		}
	}
	template <class V> void graph<V>::TopoSortDFSBack(vector<VExtern*>& sequence)const
	{
		vector<VExtern*> stack;
		size_t i;
		VExtern* head;
		VExtern* next;
		VExtern* now;
		vector<size_t> label;
		label.recount(content.count());
		//compress();
		sequence.clear();
		for (i = 0; i < content.count(); i++)
		{
			now = content[i];
			label[i] = 0;
			if (now != NULL)
			{
				label[i] = now->out.count();
				if (label[i] == 0) stack.append(now);
			}
		}
		
		for (i = 0; i < content.count(); i++)
		{
			now = content[i];
			
		}
		while (stack.pop(head) != 0)
		{
			sequence.append(head);
			for (i = 0; i < head->in.count(); i++)
			{
				next = head->in[i];
				if (label[next->site()] == 0)
				{
					throw PikaError("TopoSortDFS", "label[next] == 0", next->site());
				}
				label[next->site()] -= 1;
				if (label[next->site()] == 0)
				{
					stack.append(next);
				}
			}
		}
	}
	template <class V> void graph<V>::TopoSortBFSBack(vector<VExtern*>& sequence)const
	{
		buffer<VExtern*> stack;
		size_t i;
		VExtern* head;
		VExtern* now;
		VExtern* next;
		vector<size_t> label;
		label.recount(content.count());
		//compress();
		sequence.clear();
		for (i = 0; i < content.count(); i++)
		{
			now = content[i];
			label[i] = 0;
			if (now != NULL)
			{
				label[i] = now->out.count();
				if (label[i] == 0) stack.append(now);
			}
		}
		
		while (stack.dequeue(head) != 0)
		{
			sequence.append(head);
			for (i = 0; i < head->in.count(); i++)
			{
				next = head->in[i];
				if (label[next->site()] == 0)
				{
					throw PikaError("TopoSortDFS", "label[next] == 0", next->site());
				}
				label[next->site()] -= 1;
				if (label[next->site()] == 0)
				{
					stack.append(next);
				}
			}
		}
	}

	template <class V> void graph<V>::BFTbackward(vector<bool> & label, buffer<VExtern*>& queue)const
	{
		size_t i;
		VExtern* head;
		VExtern* next;
		label.recount(content.count());
		label.value(false);
		while (queue.dequeue(head))
		{
			if (label[head->site()] == false)
			{
				label[head->site()] = true;
				for (i = 0; i < head->InDegree(); i++)
				{
					next = head->In(i);
					if (label[next->site()] == false) queue.append(next);
				}
			}
		}
	}
	template <class V> void graph<V>::Shrink(const vector<bool>& label, vector<VExtern*>& sequence) const
	{
		size_t new_count, i;
		new_count = 0;
		for (i = 0; i < sequence.count(); i++)
		{
			if (label[sequence[i]->site()])
			{
				sequence[new_count] = sequence[i];
				//sequence[new_count]->label_site = new_count;
				new_count += 1;
			}
		}
		sequence.recount(new_count);
	}

	template <class V> void graph<V>::lift(VExtern* target, VExtern* src)
	{
		size_t i;
		VExtern* up;
		size_t up_in;
		try
		{
			for (i = 0; i < target->OutDegree(); i++)
			{
				//printf("%zu:%zu\n", target->OutDegree(), i);
				up = target->out[i];
				up_in = up->SearchIn(target);
				up->in[up_in] = src;
				src->AppendOut(up);
			}
		}
		catch (hyperlex::dictionary* error)
		{
			//printf("11111???\n");
			error->append("loaction", "graph<V>::lift");
			throw error;
		}
		target->out.clear();
	}
	// dst:up, target:middle, src:down
	template <class V> void graph<V>::lift(VExtern* dst, VExtern* target, VExtern* src)
	{
		size_t up_in;
		//size_t middle_in;
		size_t middle_out;

		try
		{
			middle_out = target->SearchOut(dst);
			//down_out = vertice[down].SearchOut(middle, "lift");
			up_in = dst->SearchIn(target);
			//middle_in = vertice[middle].SearchIn(down, "lift");

			src->AppendOut(dst);
			dst->in[up_in] = src;
			target->ShrinkOut(middle_out);
		}
		catch (hyperlex::dictionary* error)
		{
			error->append("loaction", "graph<V>::lift");
			throw error;
		}
	}
	
	template <class V> void graph<V>::OutputGive(vector<size_t>& label) const
	{
		size_t i;
		label.recount(content.count());
		for (i = 0; i < content.count(); i++)
		{
			if (content[i]!=NULL) label[i] = content[i]->OutDegree();
			else label[i] = 0;
		}
	}
	template <class V> void graph<V>::OutputCut(vector<size_t>& label, size_t target) const
	{
		size_t i;
		VExtern* now;
		now = content[target];
		for (i = 0; i < now->InDegree(); i++)
		{
			label[now->In(i)->site()] -= 1;
		}
	}

	template <class V> vortex<V>::~vortex()
	{
		size_t i, site;
		Vextern* target;
		try
		{
			target = (Vextern*)infor;
			for (i = 0; i < in.count(); i++)
			{
				site = in[i]->SearchOutExcept(target);
				in[i]->ShrinkOut(site);
			}
			for (i = 0; i < out.count(); i++)
			{
				site = out[i]->SearchInExcept(target);
				out[i]->ShrinkIn(site);
			}
		}
		catch (hyperlex::dictionary* error)
		{
			error->append("location", "vortex<V>::~vortex()");
			error->append("i", i);
			throw error;
		}
	}
	template <class V> void vortex<V>::CopyCore(const Vextern& source)
	{
		temp = source.temp;
		label_site = source.label_site;
		label_2 = source.label_2;
		label_3 = source.label_3;
		infor = source.infor;
		//V::copy((const V)source);
		out.copy(source.out);
		in.copy(source.in);
	}
	template <class V> void vortex<V>::CopyToCore(Vextern& dst) const
	{
		dst.temp = temp;
		dst.label_site = label_site;
		dst.label_2 = label_2;
		dst.label_3 = label_3;
		dst.infor = infor;
		//V::copy((const V)source);
		dst.out.copy(out);
		dst.in.copy(in);
	}
	template <class V> void vortex<V>::demo(FILE* fp)const
	{
		size_t i;
		fprintf(fp, "InDegree: %zu, InCapacity: %zu, ", in.count(), in.capacity());
		fprintf(fp, "OutDegree: %zu, OutCapacity: %zu\n", out.count(), out.capacity());
		if (in.count() != 0) fprintf(fp, "In[%zu] = %zu", (size_t)0, in[0]->label_site);
		for (i = 1; i < in.count(); i++)
			fprintf(fp, ", In[%zu] = %zu", i, in[i]->label_site);
		fprintf(fp, "\n");

		if (out.count() != 0) fprintf(fp, "Out[%zu] = %zu", (size_t)0, out[0]->label_site);
		for (i = 1; i < out.count(); i++)
			fprintf(fp, ", Out[%zu] = %zu", i, out[i]->label_site);
		fprintf(fp, "\n");
		//V::demo(fp);
	}

	template<class V> size_t vortex<V>::AppendIn(Vextern* II)
	{
		in.append(II);
		return in.count() - 1;
	}
	template<class V> size_t vortex<V>::AppendOut(Vextern* II)
	{
		out.append(II);
		return out.count() - 1;
	}
	template<class V> size_t vortex<V>::SearchIn(Vextern* label) const
	{
		size_t T;
		for (T = 0; T < in.count(); T++)
		{
			if (in[T] == label) break;
		}
		return T;
	}
	template<class V> size_t vortex<V>::SearchOut(Vextern* label) const
	{
		size_t T;
		for (T = 0; T < out.count(); T++)
		{
			if (out[T] == label) break;
		}
		return T;
	}
	template<class V> size_t vortex<V>::SearchInExcept(Vextern* label) const
	{
		size_t T;
		for (T = 0; T < in.count(); T++)
		{
			if (in[T] == label) break;
		}
		if (T == in.count())
		{
			hyperlex::dictionary* error;
			error = new hyperlex::dictionary;
			error->append("location", "void vortex<V>::SearchIn");
			error->append("error", "T == in.count()");
			error->append("T", T);
			throw error;
		}
		return T;
	}
	template<class V> size_t vortex<V>::SearchOutExcept(Vextern* label) const
	{
		size_t T;
		for (T = 0; T < out.count(); T++)
		{
			if (out[T] == label) break;
		}
		if (T == out.count())
		{
			hyperlex::dictionary* error;
			error = new hyperlex::dictionary;
			error->append("location", "void vortex<V>::SearchOut");
			error->append("error", "T == out.count()");
			error->append("T", T);
			throw error;
		}
			
		return T;
	}
	template <class V> void vortex<V>::ShrinkIn(size_t site)
	{
		if (site >= in.count())
		{
			hyperlex::dictionary* error;
			error = new hyperlex::dictionary;
			error->append("location", "void vortex<V>::ShrinkIn");
			error->append("error", "site >= in.count()");
			error->append("site", site);
			error->append("count", in.count());
			throw error;
		}
		in.shrink(site);
	}
	template <class V> void vortex<V>::ShrinkOut(size_t site)
	{
		if (site >= out.count())
		{
			hyperlex::dictionary* error;
			error = new hyperlex::dictionary;
			error->append("location", "void vortex<V>::ShrinkOut");
			error->append("error", "site >= out.count()");
			error->append("site", site);
			error->append("count", out.count());
			throw error;
		}
		out.shrink(site);
	}

	template <class V> void vortex<V>::BackNext(iteratorS<Vextern>& iter)
	{
		size_t i;
		Vextern* now;
		int SS;
		if (!iter.still()) return;
		now = iter.target();
		SS = iter.state();
		iter.pop();
		if (SS == 0)
		{
			for (i = now->in.count(); i != (size_t)0; i--)
			{
				iter.append(now, (int)i);
				iter.append(now->in[i - 1]);
			}
		}
	}
}
namespace Pikachu
{
	template <class V> void graph2<V>::vortex::refresh(void)
	{
		InDegree = 0;
		OutDegree = 0;
		InCapacity = 0;
		OutCapacity = 0;
		In = NULL;
		Out = NULL;
		content = NULL;


		Next = _uintMax_;
		SetNotValid();
		
	}
	template <class V> void graph2<V>::vortex::ruin(void)
	{
		free(In);
		In = NULL;
		free(Out);
		Out = NULL;
		InDegree = 0;
		OutDegree = 0;
		InCapacity = 0;
		OutCapacity = 0;


		delete content;
		content = NULL;

	}
	template<class V> size_t graph2<V>::vortex::AppendIn(size_t II)
	{
		size_t should, new_size;
		if (InDegree >= InCapacity)
		{
			new_size = (InCapacity + InCapacity / 2 + 2);
			In = (size_t*)realloc(In, new_size * sizeof(size_t));
			InCapacity = new_size;
		}
		should = InDegree;
		InDegree += 1;
		In[should] = II;
		return should;
	}
	template<class V> size_t graph2<V>::vortex::AppendOut(size_t OO)
	{
		size_t should, new_size;
		if (OutDegree >= OutCapacity)
		{
			new_size = (OutCapacity + OutCapacity / 4 + 8);
			Out = (size_t*)realloc(Out, new_size * sizeof(size_t));
			OutCapacity = new_size;
		}
		should = OutDegree;
		OutDegree += 1;
		Out[should] = OO;
		return should;
	}
	template <class V> void graph2<V>::vortex::RecountIn(size_t count)
	{
		In = (size_t*)realloc(In, count * sizeof(size_t));
		InCapacity = count;
		InDegree = count;
	}
	template <class V> void graph2<V>::vortex::RecountOut(size_t count)
	{
		Out = (size_t*)realloc(Out, count * sizeof(size_t));
		OutCapacity = count;
		OutDegree = count;
	}
	template <class V> void graph2<V>::vortex::SetValid(void)
	{
		Next = _uintMax_ - 1;
	}
	template <class V> void graph2<V>::vortex::SetNotValid(void)
	{

	}
	template<class V> bool graph2<V>::vortex::IfValid(void) const
	{
		return Next == (_uintMax_ - 1);
	}
	template <class V> void graph2<V>::vortex::copy(const graph2<V>::vortex& source)
	{ 
		size_t i;
		InDegree = source.InDegree;
		OutDegree = source.OutDegree;
		InCapacity = source.InCapacity;
		OutCapacity = source.OutCapacity;
		In = (size_t*)malloc(InCapacity * sizeof(size_t));
		Out = (size_t*)malloc(OutCapacity * sizeof(size_t));

		for (i = 0; i < InDegree; i++)
			In[i] = source.In[i];
		for (i = 0; i < OutDegree; i++)
			Out[i] = source.Out[i];


		if(source.IfValid()) content = source.content->copy();

		Next = source.Next;
	}
	template <class V> void graph2<V>::vortex::Demo(FILE* fp)const
	{
		size_t i;
		if (IfValid())
		{
			fprintf(fp, "InDegree: %zu, InCapacity: %zu, ", InDegree, InCapacity);
			fprintf(fp, "OutDegree: %zu, OutCapacity: %zu\n", OutDegree, OutCapacity);
			if (InDegree != 0) fprintf(fp, "In[%zu] = %zu", (size_t)0, In[0]);
			for (i = 1; i < InDegree; i++)
				fprintf(fp, ", In[%zu] = %zu", i, In[i]);
			fprintf(fp, "\n");

			if (OutDegree != 0) fprintf(fp, "Out[%zu] = %zu", (size_t)0, Out[0]);
			for (i = 1; i < OutDegree; i++)
				fprintf(fp, ", Out[%zu] = %zu", i, Out[i]);
			fprintf(fp, "\n");
		}
	}

	template<class V> size_t graph2<V>::vortex::SearchIn(size_t label) const
	{
		size_t T;
		for (T = 0; T < InDegree; T++)
		{
			if (In[T] == label) break;
		}
		return T;
	}
	template<class V> size_t graph2<V>::vortex::SearchOut(size_t label) const
	{
		size_t T;
		for (T = 0; T < OutDegree; T++)
		{
			if (Out[T] == label) break;
		}
		return T;
	}
	template<class V> size_t graph2<V>::vortex::SearchIn(size_t label, const char* error) const
	{
		size_t T;
		for (T = 0; T < InDegree; T++)
		{
			if (In[T] == label) break;
		}
		if (T == InDegree)
			throw PikaError(error, "SearchIn: T == InDegree", T);
		return T;
	}
	template<class V> size_t graph2<V>::vortex::SearchOut(size_t label, const char* error) const
	{
		size_t T;
		for (T = 0; T < OutDegree; T++)
		{
			if (Out[T] == label) break;
		}
		if(T == OutDegree) 
			throw PikaError(error, "SearchOut: T == OutDegree", T);
		return T;
	}
	template <class V> void graph2<V>::vortex::ShrinkIn(size_t site)
	{
		size_t i;
		if (site >= InDegree) 
			throw PikaError("graph2<V>::vortex::ShrinkIn", "site >= InDegree", site);
		for (i = site + 1; i < InDegree; i++)
		{
			In[i - 1] = In[i];
		}
		InDegree -= 1;
	}
	template <class V> void graph2<V>::vortex::ShrinkOut(size_t site)
	{
		size_t i;
		if (site >= OutDegree) 
			throw PikaError("graph2<V>::vortex::ShrinkOut", "site >= OutDegree", site);
		for (i = site + 1; i < OutDegree; i++)
		{
			Out[i - 1] = Out[i];
		}
		OutDegree -= 1;
	}


	template <class V> graph2<V>::graph2()
	{
		firstVainVortex = _uintMax_;
		vortexCount = 0;
	}
	template <class V> graph2<V>::~graph2()
	{
		//array<bool> label;
		size_t now;
		//label.Realloc(vertice.length());
		//label.value(true);
		//now = firstVainVortex;
		//while (now ！ = _uintMax_)
		//{
		//	laebl[now] = false;
		//	now = vertice[now].FirstIn;
		//}
		for (now = 0; now < vertice.length(); now++)
			if (vertice[now].IfValid()) vertice[now].ruin();
	}
	template <class V> void graph2<V>::clear(void)
	{
		size_t now;
		for (now = 0; now < vertice.length(); now++)
			if (vertice[now].IfValid()) vertice[now].ruin();
	}
	template <class V> size_t graph2<V>::capacity(void)const
	{
		return vertice.length();
	}
	template <class V> size_t graph2<V>::AppendVortex(void)
	{
		size_t site;
		size_t OldCount, NewCount, i;
		if (firstVainVortex == _uintMax_)
		{
			OldCount = vertice.length();
			NewCount = OldCount + OldCount / 4 + 8;
			vertice.Realloc(NewCount);
			for (i = OldCount; i < NewCount; i++)
			{
				vertice[i].refresh();
				vertice[i].Next = i + 1;
			}
			firstVainVortex = OldCount;
			vertice[NewCount - 1].Next = _uintMax_;
		}
		site = firstVainVortex;
		firstVainVortex = vertice[firstVainVortex].Next;
		vortexCount += 1;
		vertice[site].Next = _uintMax_;
		vertice[site].SetValid();
		return site;
	}
	template <class V> void graph2<V>::append(size_t from, size_t to)
	{
		vertice[from].AppendOut(to);
		vertice[to].AppendIn(from);
		return;
	}
	template <class V> void graph2<V>::append(size_t srcL, size_t srcR, size_t to)
	{

		vertice[srcL].AppendOut(to);
		vertice[to].AppendIn(srcL);
		vertice[srcR].AppendOut(to);
		vertice[to].AppendIn(srcR);
	}
	template <class V> void graph2<V>::append(size_t srcL, size_t srcM, size_t srcR, size_t to)
	{
		vertice[srcL].AppendOut(to);
		vertice[to].AppendIn(srcL);

		vertice[srcM].AppendOut(to);
		vertice[to].AppendIn(srcM);

		vertice[srcR].AppendOut(to);
		vertice[to].AppendIn(srcR);
	}
	template <class V> size_t graph2<V>::append(V* C)
	{
		size_t site;
		site = AppendVortex();
		vertice[site].content = C->copy();
		return site;
	}
	template <class V> void graph2<V>::append(const graph2& source, vector<size_t>& label)
	{
		size_t i, site, j;
		vortex* DD;
		const vortex* SS;
		label.clear();
		label.recount(source.vertice.length());
		for (i = 0; i < label.count(); i++)
		{
			if (source.vertice[i].IfValid())
				label[i] = append(source.vertice[i].content);
		}
		for (i = 0; i < label.count(); i++)
		{
			SS = source.vertice.ptr(i);
			if (!SS->IfValid()) continue;
			site = label[i];
			DD = vertice.ptr(site);
			DD->RecountIn(SS->InDegree);
			DD->RecountOut(SS->OutDegree);
			for (j = 0; j < SS->InDegree; j++)
				DD->In[j] = label[SS->In[j]];
			for (j = 0; j < SS->OutDegree; j++)
				DD->Out[j] = label[SS->Out[j]];
		}
	}
	template <class V> size_t graph2<V>::MoveAppend(V* C)
	{
		size_t site;
		site = AppendVortex();
		vertice[site].content = C;
		return site;
	}
	template <class V> typename graph2<V>::vortex& graph2<V>::SV(const size_t No)
	{
		return vertice[No];
	}
	template <class V> graph2<V>* graph2<V>::copy(void) const
	{
		graph2<V>* GG;
		GG = new graph2<V>();
		GG->copy(*this);
		return GG;
	}
	template <class V> void graph2<V>::copy(const graph2<V>& source)
	{
		size_t now;
		for (now = 0; now < vertice.length(); now++)
			if (vertice[now].IfValid()) vertice[now].ruin();

		vertice.Realloc(source.vertice.length());
		for (now = 0; now < vertice.length(); now++)
		{
			vertice[now].copy(source.vertice[now]);
		}
		firstVainVortex = source.firstVainVortex;
		vortexCount = source.vortexCount;
	}
	template <class V> void graph2<V>::BFTforward(vector<size_t>& label, buffer<size_t>& queue) const
	{
		size_t head, i, next;
		const vortex* now;
		label.recount(vertice.length());
		label.value(0);

		while (queue.dequeue(head))
		{
			if (label[head] == 0)
			{
				label[head] = 1;
				now = vertice.ptr(head);
				for (i = 0; i < now->OutDegree; i++)
				{
					next = now->Out[i];
					if (label[next] == 0) queue.append(next);
				}
			}
		}
	}
	template <class V> void graph2<V>::BFTbackward(vector<size_t>& label, buffer<size_t>& queue) const
	{
		size_t head, i, next;
		const vortex* now;
		label.recount(vertice.length());
		label.value(0);
		while (queue.dequeue(head))
		{
			if (label[head] == 0)
			{
				label[head] = 1;
				now = vertice.ptr(head);
				for (i = 0; i < now->InDegree; i++)
				{
					next = now->In[i];
					if (label[next] == 0) queue.append(next);
				}
			}
		}
	}
	template <class V> void graph2<V>::path(vector<size_t>& label, buffer<size_t>& queue, size_t from, size_t to) const
	{
		vector<size_t> label1, label2;
		size_t i;
		queue.clear();
		queue.append(from);
		BFTforward(label1, queue);
		queue.clear();
		queue.append(to);
		BFTbackward(label2, queue);
		label.recount(vertice.length());
		for (i = 0; i < vertice.length(); i++)
			label[i] = (size_t)(label1[i] && label2[i]);
	}
	template <class V> void graph2<V>::TopologicalSorting(vector<size_t>& sequence)const
	{
		vector<size_t> label;
		buffer<size_t> queue;
		size_t head, i, next;
		const vortex* now;
		label.recount(vertice.length());
		sequence.clear();
		for (i = 0; i < vertice.length(); i++)
		{
			label[i] = vertice[i].InDegree;
			if (label[i] == 0 && vertice[i].IfValid()) queue.append(i);
		}
		while (queue.dequeue(head))
		{
			sequence.append(head);
			now = vertice.ptr(head);
			for (i = 0; i < now->OutDegree; i++)
			{
				next = now->Out[i];
				if (label[next] == 0)
				{
					throw PikaError("TopologicalSorting", "label[next] == 0", next);
				}
				label[next] -= 1;
				if (label[next] == 0)
				{
					queue.append(next);
				}
			}
		}
	}
	template <class V> void graph2<V>::TopoSortDFT(vector<size_t>& sequence)const
	{
		vector<size_t> label;
		vector<size_t> stack;
		size_t head, i, next;
		const vortex* now;
		label.recount(vertice.length());
		sequence.clear();
		for (i = 0; i < vertice.length(); i++)
		{
			label[i] = vertice[i].InDegree;
			if (label[i] == 0 && vertice[i].IfValid()) stack.append(i);
		}
		while (stack.pop(head) != 0)
		{
			sequence.append(head);
			now = vertice.ptr(head);
			for (i = 0; i < now->OutDegree; i++)
			{
				next = now->Out[i];
				if (label[next] == 0)
				{
					throw PikaError("TopoSortDFT", "label[next] == 0", next);
				}
				label[next] -= 1;
				if (label[next] == 0)
				{
					stack.append(next);
				}
			}
		}
	}
	template <class V> void graph2<V>::TopologicalSortingBack(vector<size_t>& sequence)const
	{
		vector<size_t> label;
		buffer<size_t> queue;
		size_t head, i, next;
		const vortex* now;
		label.recount(vertice.length());
		sequence.clear();
		for (i = 0; i < vertice.length(); i++)
		{
			label[i] = vertice[i].OutDegree;
			if (label[i] == 0 && vertice[i].IfValid()) queue.append(i);
		}
		while (queue.dequeue(head))
		{
			sequence.append(head);
			now = vertice.ptr(head);
			for (i = 0; i < now->InDegree; i++)
			{
				next = now->In[i];
				if (label[next] == 0)
				{
					throw PikaError("TopologicalSortingBack", "label[next] == 0", next);
				}
				label[next] -= 1;
				if (label[next] == 0)
				{
					queue.append(next);
				}
			}
		}
	}
	template <class V> void graph2<V>::SortingShrink(vector<size_t>& label, vector<size_t>& sequence) const
	{
		size_t new_count, now, i;
		new_count = 0;
		for (i = 0; i < sequence.count(); i++)
		{
			if (label[sequence[i]] != 0)
			{
				sequence[new_count] = sequence[i];
				new_count += 1;
			}
		}
		sequence.recount(new_count);
	}

	template <class  V> typename graph2<V>::vortex& graph2<V>::operator[](size_t target)
	{
		return vertice[target];
	}
	template <class  V> const typename graph2<V>::vortex& graph2<V>::operator[](size_t target) const
	{
		return vertice[target];
	}
	template <class  V> typename graph2<V>::vortex& graph2<V>::In(size_t source, size_t No)
	{
		return vertice[vertice[source].In[No]];
	}
	template <class V> void graph2<V>::TraverseInitial(vector<size_t>& label, vector<size_t>& stack) const
	{
		label.recount(vertice.length());
		label.value(0);
		stack.clear();
	}
	template <class V> void graph2<V>::TraverseNextBack(vector<size_t>& label, vector<size_t>& stack) const
	{
		size_t fromer;
		size_t now;
		if (stack.top(now) == 0) return;
		if (label[now] == vertice[now].InDegree)
		{
			stack.pop();
			if (stack.top(fromer) == 0) return;
			label[now] = 0;
			label[fromer] += 1;
		}
		else
		{
			stack.append(vertice[now].In[label[now]]);
		}
	}
	template <class V> void graph2<V>::lift(size_t middle, size_t down)
	{
		size_t up, i;
		size_t up_in;
		size_t down_out;
		size_t middle_in;
		size_t middle_out;
		
		try
		{
			for (i = 0; i < vertice[middle].OutDegree; i++)
			{
				up = vertice[middle].Out[i];
				up_in = vertice[up].SearchIn(middle, "lift");

				vertice[up].In[up_in] = down;
				vertice[down].AppendOut(up);
			}
		}
		catch (const PikaError& E)
		{
			throw PikaError(E, "graph2<V>::lift");
		}
		

		free(vertice[middle].Out);
		vertice[middle].Out = NULL;
		vertice[middle].OutCapacity = 0;
		vertice[middle].OutDegree = 0;
	}
	template <class V> void graph2<V>::lift(size_t up, size_t middle, size_t down)
	{
		size_t up_in;
		size_t down_out;
		//size_t middle_in;
		size_t middle_out;

		try
		{
			middle_out = vertice[middle].SearchOut(up, "lift");
			//down_out = vertice[down].SearchOut(middle, "lift");
			up_in = vertice[up].SearchIn(middle, "lift");
			//middle_in = vertice[middle].SearchIn(down, "lift");
			
			vertice[down].AppendOut(up);
			vertice[up].In[up_in] = down;
			vertice[middle].ShrinkOut(middle_out);
		}
		catch (const PikaError& E)
		{
			throw PikaError(E, "graph2<V>::lift");
		}
	}
	template <class V> void graph2<V>::LiftLeft(size_t target)
	{
		if (vertice[target].InDegree < 1)
			throw PikaError("graph2<V>::LiftLeft", "vertice[target].InDegree < 1", vertice[target].InDegree);
		lift(target, vertice[target].In[0]);
		VertexDelete(target);
	}
	template <class V> void graph2<V>::LiftRight(size_t target)
	{
		if(vertice[target].InDegree < 2)
			throw PikaError("graph2<V>::LiftRight", "vertice[target].InDegree < 2", vertice[target].InDegree);
		lift(target, vertice[target].In[1]);
		VertexDelete(target);
	}
	template <class V> size_t graph2<V>::LiftLeft(size_t target, size_t OldOutput)
	{
		size_t down;
		if (vertice[target].InDegree < 1)
			throw PikaError("graph2<V>::LiftLeft", "vertice[target].InDegree < 1", vertice[target].InDegree);
		down = vertice[target].In[0];
		lift(target, down);
		VertexDelete(target);
		if (target == OldOutput) return down;
		else return OldOutput;
	}
	template <class V> size_t graph2<V>::LiftRight(size_t target, size_t OldOutput)
	{
		size_t down;
		if (vertice[target].InDegree < 2)
			throw PikaError("graph2<V>::LiftRight", "vertice[target].InDegree < 2", vertice[target].InDegree);
		down = vertice[target].In[1];
		lift(target, down);
		VertexDelete(target);
		if (target == OldOutput) return down;
		else return OldOutput;
	}
	template <class V> void graph2<V>::VertexDelete(size_t target)
	{
		size_t i;
		size_t F, T, j;
		size_t from;
		size_t to;
		from = target;
		for (j = 0; j < vertice[target].OutDegree; j++)
		{
			to = vertice[target].Out[j];
			T = vertice[to].SearchIn(from);
			vertice[to].ShrinkIn(T);
		}
		
		to = target;
		for (j = 0; j < vertice[target].InDegree; j++)
		{
			from = vertice[target].In[j];
			F = vertice[from].SearchOut(to);
			vertice[from].ShrinkOut(F);
		}



		vertice[target].ruin();

		vertice[target].Next = firstVainVortex;
		firstVainVortex = target;
		vortexCount -= 1;
	}
	template <class V> void graph2<V>::ArcDelete(size_t from, size_t to)
	{
		size_t F, T, i;

		T = vertice[to].SearchIn(from);
		if (T == vertice[to].InDegree) 
			throw PikaError("graph2<V>::ArcDelete", "T == vertice[to].InDegree", T);
		F = vertice[from].SearchOut(to);
		if (F == vertice[from].OutDegree)
			throw PikaError("graph2<V>::ArcDelete", "F == vertice[from].OutDegree", F);

		vertice[to].ShrinkIn(T);
		vertice[from].ShrinkOut(F);
	}

	template <class V> void graph2<V>::OutputGive(vector<size_t>& label) const
	{
		size_t i;
		label.recount(vertice.length());
		for (i = 0; i < vertice.length(); i++)
		{
			if (vertice[i].IfValid()) label[i] = vertice[i].OutDegree;
			else label[i] = 0;
		}
	}
	template <class V> void graph2<V>::OutputCut(vector<size_t>& label, size_t target) const
	{
		size_t i;
		for (i = 0; i < vertice[target].InDegree; i++)
		{
			label[vertice[target].In[i]] -= 1;
		}
	}
}
namespace Pikachu
{
	template <class V, class A> void graph1<V, A>::vortex::refresh(void)
	{
		InDegree = 0;
		OutDegree = 0;
		InCapacity = 0;
		OutCapacity = 0;
		In = NULL;
		Out = NULL;
		content = NULL;
	}
	template <class V, class A> void graph1<V, A>::vortex::ruin(void)
	{
		free(In);
		free(Out);
		content = NULL;
	}
	template<class V, class A> size_t graph1<V, A>::vortex::AppendIn(size_t II)
	{
		size_t should, new_size;
		if (InDegree >= InCapacity)
		{
			new_size = (InCapacity + InCapacity / 4 + 8);
			In = (size_t*)realloc(In, new_size * sizeof(size_t));
			InCapacity = new_size;
		}
		should = InDegree;
		InDegree += 1;
		In[should] = II;
		return should;
	}
	template<class V, class A> size_t graph1<V, A>::vortex::AppendOut(size_t OO)
	{
		size_t should, new_size;
		if (OutDegree >= OutCapacity)
		{
			new_size = (OutCapacity + OutCapacity / 4 + 8);
			Out = (size_t*)realloc(Out, new_size * sizeof(size_t));
			OutCapacity = new_size;
		}
		should = OutDegree;
		OutDegree += 1;
		Out[should] = OO;
		return should;
	}
	template <class V, class A> graph1<V, A>::graph1()
	{
		firstVainArc = _uintMax_;
		firstVainVortex = _uintMax_;
		arcsCount = 0;
		vortexCount = 0;
	}
	template <class V, class A> graph1<V, A>::~graph1()
	{
		array<bool> label;
		size_t now;
		label.Realloc(vertice.length());
		label.value(true);
		now = firstVainVortex;
		while (now != _uintMax_)
		{
			label[now] = false;
			now = vertice[now].FirstIn;
		}
		for (now = 0; now < vertice.length(); now++)
			if (label[now]) vertice[now].ruin();
	}
	template <class V, class A> size_t graph1<V, A>::AppendVortex(void)
	{
		size_t site;
		size_t OldCount, NewCount, i;
		if (firstVainVortex == _uintMax_)
		{
			OldCount = vertice.length();
			NewCount = OldCount + OldCount / 4 + 8;
			vertice.Realloc(NewCount);
			for (i = OldCount; i < NewCount; i++)
			{
				vertice[i].refresh();
				vertice[i].Next = i + 1;
			}
			firstVainVortex = OldCount;
			vertice[NewCount - 1].Next = _uintMax_;
		}
		site = firstVainVortex;
		firstVainVortex = vertice[firstVainVortex].Next;
		vortexCount += 1;
		vertice[site].Next = _uintMax_;
		return site;
	}
	template <class V, class A> size_t graph1<V, A>::AppendArc(void)
	{
		size_t site;
		size_t OldCount, NewCount, i;
		if (firstVainArc == _uintMax_)
		{
			OldCount = arcs.length();
			NewCount = OldCount + OldCount / 4 + 8;
			arcs.Realloc(NewCount);
			for (i = OldCount; i < NewCount; i++)
			{
				arcs[i].refresh();
				arcs[i].FromSite = i + 1;
			}
			firstVainArc = OldCount;
			arcs[NewCount - 1].FromSite = _uintMax_;
		}
		site = firstVainArc;
		firstVainArc = arcs[firstVainArc].FromSite;
		arcsCount += 1;
		arcs[site].FromSite = _uintMax_;
		return site;
	}
	template <class V, class A> size_t graph1<V, A>::append(size_t from, size_t to, A* C)
	{
		size_t site;
		site = AppendArc();
		arcs[site].from = from;
		arcs[site].to = to;
		arcs[site].content = C.copy();
		arcs[site].FromSite = vertice[from].AppendOut(site);
		arcs[site].ToSite = vertice[to].AppendIn(site);
		return site;
	}
	template <class V, class A> size_t graph1<V, A>::append(V* C)
	{
		size_t site;
		site = AppendVortex();
		vertice[site].content = C.copy();
		return site;
	}
	template <class V, class A> typename graph1<V, A>::vortex& graph1<V, A>::SV(const size_t No)
	{
		return vertice[No];
	}
	template <class V, class A> typename graph1<V, A>::arc& graph1<V, A>::SA(const size_t No)
	{
		return arcs[No];
	}
	template <class V, class A> void graph1<V, A>::deleteArc(size_t site)
	{
		size_t from;
		size_t to;
		size_t fromSite_;
		size_t toSite_;
		size_t i;
		vortex* VV_;

		from = arcs[site].from;
		to = arcs[site].to;
		fromSite_ = arcs[site].FromSite;
		toSite_ = arcs[site].ToSite;
		
		VV_ = vertice.ptr(from);
		for (i = fromSite_; i + 1 < VV_->OutDegree; i++)
		{
			VV_->Out[i] = VV_->Out[i + 1];
			arcs[VV_->Out[i]].FromSite = i;
		}
		VV_->OutDegree -= 1;
		
		VV_ = vertice.ptr(to);
		for (i = toSite_; i + 1 < VV_ ->InDegree; i++)
		{
			VV_->In[i] = VV_->In[i + 1];
			arcs[VV_->In[i]].ToSite = i;
		}
		VV_->InDegree -= 1;

		arcs[site].FromSite = firstVainArc;
		firstVainArc = site;

	}
	/*
	template <class V, class A> class graph
	{
	public:
		struct vortex
		{
			size_t InDegree;
			size_t OutDegree;
			size_t FirstIn;
			size_t FirstOut;
			size_t LastIn;
			size_t LastOut;
			V* content;
			void refresh(void)
			{
				InDegree = 0;
				OutDegree = 0;
				FirstIn = _uintMax_;
				FirstOut = _uintMax_;
				LastIn = _uintMax_;
				LastOut = _uintMax_;
				content = NULL;
			}
		};
		struct arc
		{
			size_t from;
			size_t to;
			size_t NextIn;
			size_t NextOut;
			A* content;
			void refresh(void)
			{
				from = _uintMax_;
				to = _uintMax_;
				NextIn = _uintMax_;
				NextOut = _uintMax_;
				content = NULL;
			}
		};
	public:
		graph();
		~graph();
		size_t appendVortex(void);
		size_t appendArc(void);
		void append(size_t from, size_t to, A* C);
		vortex& SV(const size_t No);
		arc& SA(const size_t No);
	private:
		array<arc> arcs;
		array<vortex> vertice;
		size_t firstVainArc;
		size_t firstVainVortex;
		size_t arcsCount;
		size_t vortexCount;
	};
	template <class V, class A> graph<V, A>::graph()
	{
		firstVainArc = _uintMax_;
		firstVainVortex = _uintMax_;
		arcsCount = 0;
		vortexCount = 0;
	}
	template <class V, class A> graph<V, A>::~graph()
	{
	}
	template <class V, class A> size_t graph<V, A>::appendVortex(void)
	{
		size_t site;
		size_t OldCount, NewCount, i;
		if (firstVainVortex == _uintMax_)
		{
			OldCount = vertice.length();
			NewCount = OldCount + OldCount / 4 + 8;
			vertice.Realloc(NewCount);
			for (i = OldCount; i < NewCount; i++)
			{
				vertice[i].refresh();
				vertice[i].FirstIn = i + 1;
			}
			firstVainVortex = OldCount;
			vertice[NewCount - 1].FirstIn = _uintMax_;
		}
		site = firstVainVortex;
		firstVainVortex = vertice[firstVainVortex].FirstIn;
		vortexCount += 1;
		vertice[site].FirstIn = _uintMax_;
		return site;
	}
	template <class V, class A> size_t graph<V, A>::appendArc(void)
	{
		size_t site;
		size_t OldCount, NewCount, i;
		if (firstVainArc == _uintMax_)
		{
			OldCount = arcs.length();
			NewCount = OldCount + OldCount / 4 + 8;
			arcs.Realloc(NewCount);
			for (i = OldCount; i < NewCount; i++)
			{
				arcs[i].refresh();
				arcs[i].NextIn = i + 1;
			}
			firstVainArc = OldCount;
			arcs[NewCount - 1].NextIn = _uintMax_;
		}
		site = firstVainArc;
		firstVainArc = arcs[firstVainArc].NextIn;
		arcsCount += 1;
		arcs[site].NextIn = _uintMax_;
		return site;
	}

	template <class V, class A> void graph<V, A>::append(size_t from, size_t to, A* C)
	{
		size_t site;
		site = appendArc();
		arcs[site].from = from;
		arcs[site].to = to;
		arcs[site].content = C;

		vertice[from].OutDegree += 1;
		if (vertice[from].FirstOut == _uintMax_)
			vertice[from].FirstOut = site;
		else
			arcs[vertice[from].LastOut].NextOut = site;
		vertice[from].LastOut = site;


		vertice[to].InDegree += 1;



		FirstIn = _uintMax_;
		FirstOut = _uintMax_;
		LastIn = _uintMax_;
		LastOut = _uintMax_;
		content = NULL;
		from = _uintMax_;
		to = _uintMax_;
		NextIn = _uintMax_;
		NextOut = _uintMax_;
		content = NULL;
	}

	template <class V, class A> graph<V, A>::vortex& graph<V, A>::SV(const size_t No)
	{
		return vertice[No];
	}
	template <class V, class A> graph<V, A>::arc& graph<V, A>::SA(const size_t No)
	{
		return arcs[No];
	}
	*/
	


}
#undef _uintMax_

#endif



