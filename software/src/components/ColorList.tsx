import { useState } from "react";
import { FlatList, View } from "react-native";
import { styles } from "../styles/ColorListPartial";
import ColorItem, { ColorItemType } from "./ColorItem";

type dataType = {
    id: string,
    color: string
}[]

const dataTest: dataType = [
    {
        id: "1",
        color: "#FF00FF"
    },
    {
        id: "2",
        color: "#FF0000"
    },
    {
        id: "3",
        color: "#000000"
    },
    {
        id: "4",
        color: "#b6a3a3"
    },
    {
        id: "5",
        color: "#235619"
    },
    {
        id: "6",
        color: "#4f33cc"
    },
    {
        id: "7",
        color: "#235619"
    },
    {
        id: "8",
        color: "#4f33cc"
    },
    {
        id: "9",
        color: "#b6a3a3"
    },
    {
        id: "10",
        color: "#235619"
    },
    {
        id: "11",
        color: "#4f33cc"
    },
    {
        id: "12",
        color: "#235619"
    },
    {
        id: "13",
        color: "#4f33cc"
    },
    {
        id: "14",
        color: "#b6a3a3"
    },
    {
        id: "15",
        color: "#235619"
    }
]

type ColorListProps = {
    enableScroll: boolean
    data?: dataType
    width?: number
    marginBottom?: number
}

function ColorList({enableScroll, data, width, marginBottom}: ColorListProps) {
    const [selectedId, setSelectedId] = useState<string>()

    return (
        <View
            style={[styles.container, {width: width, marginBottom: marginBottom ?? 50}]}
        >
            <FlatList<ColorItemType>
                data={data ?? dataTest}
                renderItem={({ item }) => {
                    const borderWidth = item.id === selectedId ? 2 : 0;

                    return <ColorItem color={item.color} onPress={() => setSelectedId(item.id)} borderWidth={borderWidth} />
                }}
                keyExtractor={(item) => item.id}
                extraData={selectedId}
                scrollEnabled={enableScroll}
                horizontal={true}
            />
        </View>
    )
}

export default ColorList;