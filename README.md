# CSCI-335-Project2-Trees
AVL implementation

This program is tasked to read the input file (CSV's), parse its lines, construct a Tree object for each line
and make the calls to the Tree_Collection class to insert tree objects into the collection. As each line of data
is read, its 41 fields are separated and the proper subset of nine of them are used to construct the
Tree object. Tree_Collection, uses the "spc_common/tree_id" pair as a unique key for inserting
the Tree objects into the encapsulated AVL tree. The TreeCollection also keeps track of the names of
all species that are stored and in which boroughs the trees are located using <set>. AVL_Tree holds all
complete trees from the census. Any blank feilds that have been declared blank or incorrectly may
invalidate that line of data. the user is asked to provide a species name/tree type in as few as one word
or as many as three. the users input is processed and the species that match or have individual consecutive
words that match are counted and that information is displayed for the user. Data comes from NYC Open Data
and can be visualized @ www.cloudred.com/labprojects/nyctrees
