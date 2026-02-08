import { useState } from "react";
import { Button, View } from "react-native";
import ColorPicker, { ColorFormatsObject, HueSlider, Panel1, Preview } from "reanimated-color-picker";
import { colorDataType } from "../data/colorData";
import { styles } from "../styles/BottomSheetColors";
import { saveToStorage } from "../utils/storage";
import ColorList from "./ColorList";
import Separator from "./Separator";



type BottomSheetColorsProps = {
    selectedId: string
    setSelectedId: Function
    data: colorDataType
    setData: Function
}

function BottomSheetColors({selectedId, setSelectedId, data, setData}: BottomSheetColorsProps) {
    const [selectedColor, setSelectedColor] = useState<string>()

    const onSelectColor = ({ hex }: ColorFormatsObject) => {
    console.log(hex);
    setSelectedColor(hex)
    }

    return (
        <View>
            <View style={styles.colorPickerContainer}>
                <ColorPicker style={styles.colorPicker} value={selectedId} onCompleteJS={onSelectColor}>
                    <Preview hideText={true} disableOpacityTexture={true} hideInitialColor={true} style={{ marginTop: 10, marginBottom: 10, borderRadius: 20, height: 50 }} />
                    <View style={styles.rowContainer}>
                        <HueSlider style={styles.hueSlider} vertical={true} />
                        <Panel1 style={styles.panel} />
                    </View>
                    <Button title="Přidat" onPress={
                        async () => {
                            const newData = [
                                ...data,
                                {
                                    color: selectedColor,
                                    isFavourite: false
                                }
                            ]

                            setData(newData);
                            await saveToStorage(newData, "colors");
                        }
                    }>
                    </Button>
                </ColorPicker>
            </View>
            <Separator />
            <ColorList enableScroll={true} 
                width={320}
                marginBottom={0}
                selectedId={selectedId}
                setSelectedId={setSelectedId}
                onlyRenderFavourite={false}
                data={data}                
            />
            <Separator />
        </View>
    )
}

export default BottomSheetColors;