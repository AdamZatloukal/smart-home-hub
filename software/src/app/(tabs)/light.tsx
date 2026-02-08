import BottomSheetBrightness from "@/src/components/BottomSheetBrightness";
import BottomSheetColors from "@/src/components/BottomSheetColors";
import { default as ColorList } from "@/src/components/ColorList";
import DashboardLight from "@/src/components/DashboardLight";
import LightSetting from "@/src/components/LightSetting";
import { styles } from "@/src/styles/light";
import { loadFromStorage } from "@/src/utils/storage";
import BottomSheet, { BottomSheetView } from '@gorhom/bottom-sheet';
import { useCallback, useEffect, useRef, useState } from "react";
import { ScrollView, Text, View } from "react-native";
import { GestureHandlerRootView } from "react-native-gesture-handler";
import { colorDataType, defaultData } from "../../data/colorData";


// add removing colors from color list and setting color straight from color picker
// add fetch for current color at startup (stored in esp - its better when we fetch if from the esp to keep it synced)


function renderWidget(widget: string | undefined, selectedId: string, setSelectedId: Function, data: colorDataType, setData: Function) {
    switch (widget) {
        case "Oblíbené":
            return <BottomSheetColors selectedId={selectedId} setSelectedId={setSelectedId} data={data} setData={setData} />
        case "Jas a rychlost":
            return <BottomSheetBrightness />
        default:
            return null
    }
}

function Light() {
    const [data, setData] = useState<colorDataType>([]);

    useEffect(() => {
        async function fetchData() {
            const colorData: colorDataType = await loadFromStorage("colors") || defaultData
            setData(colorData)
        }
        fetchData()
    }, [])

    const bottomSheetRef = useRef<BottomSheet>(null);

    const [widget, setWidget] = useState<string>()
    const [selectedColorId, setSelectedColorId] = useState<string>(defaultData[0].color);

    const handleSheetChanges = useCallback((index: number) => {
        console.log("handleSheetChanges", index)
    }, []);

    return (
        <GestureHandlerRootView>
            <View style={styles.screen}>
                <DashboardLight catchphrase="Řídící panel" colorHex={selectedColorId} data={data} setData={setData} />
                <ScrollView
                    contentContainerStyle={styles.container}
                    showsVerticalScrollIndicator={false}
                >
                    <LightSetting name="Oblíbené" bottomSheetRef={bottomSheetRef} setWidget={setWidget}>
                        <View style={styles.colorListContainer}>
                            <Text style={styles.favouriteText}>Nastav oblíbené barvy nebo přidej novou barvu</Text>
                            <ColorList enableScroll={true}
                                setSelectedId={setSelectedColorId}
                                selectedId={selectedColorId}
                                onlyRenderFavourite={true}
                                data={data} />
                        </View>
                    </LightSetting>
                    <LightSetting name="Jas a rychlost" bottomSheetRef={bottomSheetRef} setWidget={setWidget}>
                        <View style={styles.brightnessContainer}>
                            <Text style={styles.brightnessText}>
                                Jas nelze nastavit při některých režimech
                                Rychlost nelze nastavit v režimu Static
                            </Text>
                        </View>
                    </LightSetting>
                    <LightSetting name="Přizpůsobit" bottomSheetRef={bottomSheetRef} setWidget={setWidget} />
                    <LightSetting name="Přizpůsobit" bottomSheetRef={bottomSheetRef} setWidget={setWidget} />
                </ScrollView>
                <BottomSheet
                    ref={bottomSheetRef}
                    onChange={handleSheetChanges}
                    snapPoints={["25%", "60%", "80%"]}
                    enablePanDownToClose={true}
                    backgroundStyle={styles.backgroundStyles}
                    handleIndicatorStyle={styles.handleStyle}
                    index={-1}
                    enableContentPanningGesture={false}
                >
                    <BottomSheetView style={styles.contentContainer}>
                        {
                            renderWidget(widget, selectedColorId, setSelectedColorId, data, setData)
                        }
                    </BottomSheetView>
                </BottomSheet>
            </View>
        </GestureHandlerRootView >
    )
}

export default Light;