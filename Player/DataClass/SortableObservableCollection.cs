using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;

namespace Player.DataClass
{
    public class SortableObservableCollection2<T> : ObservableCollection<T>
    {

        public void Sort()
        {

            Sort(Comparer<T>.Default);

        }

        public void Sort(IComparer<T> comparer)
        {

            int i, j;

            T index;

            for (i = 0; i < Count; i++)
            {

                index = this[i];     //If you can't read it, it should be index = this[x], where x is i :-)

                j = i;

                while ((j > 0) && (comparer.Compare(this[j - 1], index) == 1))
                {

                    this[j] = this[j - 1];

                    j = j - 1;

                }

                this[j] = index;

            }

        }

    }
    /// <summary>
    /// Represents a dynamic data  collection that provides notifications when items get added, removed, or when the whole list  is refreshed and allows sorting.
    /// </summary>
    /// <typeparam name="T">The type of elements in the collection.</typeparam>
    public class SortableObservableCollection<T> : ObservableCollection<T>
    {
        /// <summary>
        /// Sorts the items of the collection in ascending order according to a key.
        /// </summary>
        /// <typeparam name="TKey">The type of the key returned by <paramref name="keySelector"/>.</typeparam>
        /// <param name="keySelector">A function to extract a key from an item.</param>
        public void Sort<TKey>(Func<T, TKey> keySelector)
        {
            InternalSort(Items.OrderBy(keySelector));
        }

        /// <summary>
        /// Sorts the items of the collection in ascending order according to a key.
        /// </summary>
        /// <typeparam name="TKey">The type of the key returned by <paramref name="keySelector"/>.</typeparam>
        /// <param name="keySelector">A function to extract a key from an item.</param>
        /// <param name="comparer">An <see cref="IComparer{T}"/> to compare keys.</param>
        public void Sort<TKey>(Func<T, TKey> keySelector, IComparer<TKey> comparer)
        {
            InternalSort(Items.OrderBy(keySelector, comparer));
        }

        /// <summary>
        /// Moves the items of the collection so that their orders are the same as those of the items provided.
        /// </summary>
        /// <param name="sortedItems">An <see cref="IEnumerable{T}"/> to provide item orders.</param>
        private void InternalSort(IEnumerable<T> sortedItems)
        {
            var sortedItemsList = sortedItems.ToList();

            foreach (var item in sortedItemsList)
            {
                Move(IndexOf(item), sortedItemsList.IndexOf(item));
            }
        }

        protected override void InsertItem(int index, T item)

      {
             Comparer<T> comparer = Comparer<T>.Default;
            
          for (int i = 0; i < this.Count; i++)

          {

              switch (Math.Sign( comparer.Compare(this[i],item)))

              {

                  case 0:

                      break;

                  case 1:

                      base.InsertItem(i, item);

                      return;

                  case -1:

                      break;

              }

          }

   

          base.InsertItem(this.Count, item);

      }
    }
}
