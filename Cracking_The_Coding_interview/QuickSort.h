#ifndef QUICKSORT_H
#define QUICKSORT_H


class QuickSort
{
    public:
        /** Default constructor */
        QuickSort();
        /** Default destructor */
        virtual ~QuickSort();
        static void learn();
        static void sort(int[],int,int);
        static int choosePivotElement(int);
    protected:
    private:
};

#endif // QUICKSORT_H
