import { fetch } from 'expo/fetch';
import { FlatList, View } from "react-native";
import { backend } from "../constants/BackendInfo";
import { colorDataType, colorDataTypeSingle } from '../data/colorData';
import { styles } from "../styles/ColorListPartial";
import { hexToRGB } from '../utils/hexrgb';
import ColorItem from "./ColorItem";

type ColorListProps = {
    enableScroll: boolean
    data: colorDataType
    width?: number
    marginBottom?: number
    setSelectedId: Function
    selectedId: string,
    onlyRenderFavourite: boolean
}

async function postDataColor(hex: string) {
    const RGBdata = hexToRGB(hex)

    const res = await fetch(backend.postUrlColor, {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify(RGBdata)
    })
    const result = await res.text()
    console.log(result) // debug
}

function ColorList({ enableScroll, data, width, marginBottom, setSelectedId, selectedId, onlyRenderFavourite }: ColorListProps) {
    return (
        <View
            style={[styles.container, { width: width, marginBottom: marginBottom ?? 50 }]}
        >
            <FlatList<colorDataTypeSingle>
                data={data}
                renderItem={({ item }) => {
                    const borderWidth = item.color === selectedId ? 2 : 0;

                    if (onlyRenderFavourite && (!item.isFavourite)) {
                        return null;
                    }

                    return <ColorItem
                        color={item.color}
                        onPress={() => {
                            setSelectedId(item.color)       // each color is unique -> hex code is the id
                            postDataColor(item.color)
                        }}
                        borderWidth={borderWidth} />
                }}
                keyExtractor={(item) => item.color}
                extraData={selectedId}
                scrollEnabled={enableScroll}
                horizontal={true}
            />
        </View>
    )
}

export default ColorList;