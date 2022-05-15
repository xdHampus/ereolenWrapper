#include <gtest/gtest.h>
#include "../main/structs/ChecklistItem.h"

TEST(CInterfaceTests, ChecklistItemManipulation) {
    struct ChecklistItem* item = ereol_ChecklistItem_instantiate();
    int creationDateUtc = "999";

    ereol_ChecklistItem_setCreationDateUTC(item, creationDateUtc);

    EXPECT_EQ(
        creationDateUtc,
        ereol_ChecklistItem_getCreationDateUTC(item)
    );
}

