/***************************************************************************
 *   Copyright (c) 2022 Peter McB                                          *
 *                                                                         *
 *   based on: TaskCreateNodeSet.h                                         *
 *   Copyright (c) 2013 Jürgen Riegel (FreeCAD@juergen-riegel.net)         *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef GUI_TASKVIEW_TaskCreateElementSet_H
#define GUI_TASKVIEW_TaskCreateElementSet_H

#include <Gui/TaskView/TaskView.h>
#include <Mod/Fem/App/FemSetElementNodesObject.h>


class Ui_TaskCreateElementSet;

class SoEventCallback;

namespace Base {
class Polygon2d;
}
namespace App {
class Property;
}

namespace Gui {
class ViewProvider;
class ViewVolumeProjection;
}

namespace FemGui {

class ViewProviderFemMesh;


class TaskCreateElementSet : public Gui::TaskView::TaskBox, public Gui::SelectionObserver
{
    Q_OBJECT

public:
    TaskCreateElementSet(Fem::FemSetElementNodesObject *pcObject,QWidget *parent = nullptr);
    ~TaskCreateElementSet();

    std::set<long> elementTempSet;
    ViewProviderFemMesh * MeshViewProvider;
        static std::string currentProject;

private Q_SLOTS:
    void Poly(void);
    void Restore(void);
    void CopyResultsMesh(void);

protected:
    Fem::FemSetElementNodesObject *pcObject;
    static void DefineElementsCallback(void * ud, SoEventCallback * n);
    void DefineNodes(const Base::Polygon2d &polygon,const Gui::ViewVolumeProjection &proj, bool);

protected:
    void onSelectionChanged(const Gui::SelectionChanges& msg) override;
    enum selectionModes {
            none,
            PickElement
        } selectionMode;

private:
    QWidget* proxy;
    Ui_TaskCreateElementSet* ui;
};

} // namespace PartDesignGui

#endif // GUI_TASKVIEW_TaskCreateElementSet_H