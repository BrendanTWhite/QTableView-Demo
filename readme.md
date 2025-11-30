# Qt QTableView based on data from a Reference

This repo is based on [this Model-View Architecture demo](https://pmsquaresoft.com/exploring-model-view-architecture-in-qt-using-c/) 
by [PM Square Soft](https://pmsquaresoft.com). Many thanks
to PM Square Soft for this simple, easy to understand example.

The only significant change I made was to move the source data QList
from a member variable on the QAbstractTableModel
to a member variable on another object (in this case, the contact manager).

This meant that the source data QList was no longer on the QAbstractTableModel itself.
I originally tried using pointers to the QList on the QAbstractTableModel, but 
the grid never actually updated. Not sure why.

So I then tried having a reference to the QList on the QAbstractTableModel, while leaving
the actual original source data QList on a separate object. This seems to work just fine.

### Danger!

This should work fine for my case, where the original QList is on the parent
of the QAbstractTableModel. This means the original QList can never disappear before
the QAbstractTableModel.

But if you have the QList on some other object,
that is not the parent of the QAbstractTableModel,
then you would need to find some other way to ensure that the QList
can never disappear before the QAbstractTableModel.
