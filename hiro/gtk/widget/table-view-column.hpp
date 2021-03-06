#if defined(Hiro_TableView)

namespace hiro {

struct pTableViewColumn : pObject {
  Declare(TableViewColumn, Object)

  auto setActive() -> void;
  auto setAlignment(Alignment alignment) -> void;
  auto setBackgroundColor(Color color) -> void;
  auto setEditable(bool editable) -> void;
  auto setExpandable(bool expandable) -> void;
  auto setFont(const Font& font) -> void override;
  auto setForegroundColor(Color color) -> void;
  auto setHorizontalAlignment(double) -> void {}
  auto setIcon(const image& icon) -> void;
  auto setResizable(bool resizable) -> void;
  auto setSorting(Sort sorting) -> void;
  auto setText(const string& text) -> void;
  auto setVerticalAlignment(double) -> void {}
  auto setVisible(bool visible) -> void override;
  auto setWidth(int width) -> void;

  auto _parent() -> maybe<pTableView&>;

  GtkTreeViewColumn* gtkColumn = nullptr;
  GtkWidget* gtkHeader = nullptr;
  GtkWidget* gtkHeaderIcon = nullptr;
  GtkWidget* gtkHeaderText = nullptr;
  GtkWidget* gtkHeaderSort = nullptr;
  GtkCellRenderer* gtkCellToggle = nullptr;
  GtkCellRenderer* gtkCellIcon = nullptr;
  GtkCellRenderer* gtkCellText = nullptr;
};

}

#endif
